package com.twinbot.touchcounter

import android.content.Context
import android.os.Handler
import android.os.Looper
import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import com.amazonaws.mobileconnectors.iot.AWSIotKeystoreHelper
import com.amazonaws.mobileconnectors.iot.AWSIotMqttClientStatusCallback
import com.amazonaws.mobileconnectors.iot.AWSIotMqttManager
import java.io.File
import java.util.UUID
import java.util.concurrent.Executors

enum class EngineState { ON, OFF }

class AwsIotClient(private val context: Context) {
    private val mqttManager: AWSIotMqttManager
    private val ioExecutor = Executors.newSingleThreadExecutor()
    private val mainHandler = Handler(Looper.getMainLooper())
    private val prefs = context.getSharedPreferences("iot_prefs", Context.MODE_PRIVATE)

    var connectionStatus by mutableStateOf("Connecting...")
        private set
    var isConnected by mutableStateOf(false)
        private set
    var lastState by mutableStateOf(loadLastState())
        private set

    init {
        val clientId = loadOrCreateClientId(context)
        mqttManager = AWSIotMqttManager(clientId, IotConfig.AWS_IOT_ENDPOINT)
        mqttManager.keepAlive = IotConfig.KEEP_ALIVE_SECONDS
    }

    fun connect() {
        ioExecutor.execute {
            try {
                val keyStore = prepareKeyStore()
                mqttManager.connect(keyStore) { status, throwable ->
                    when (status) {
                        AWSIotMqttClientStatusCallback.AWSIotMqttClientStatus.Connected -> {
                            updateConnectionState(true, "Connected")
                        }
                        AWSIotMqttClientStatusCallback.AWSIotMqttClientStatus.Connecting -> {
                            updateConnectionState(false, "Connecting...")
                        }
                        AWSIotMqttClientStatusCallback.AWSIotMqttClientStatus.Reconnecting -> {
                            updateConnectionState(false, "Reconnecting...")
                        }
                        AWSIotMqttClientStatusCallback.AWSIotMqttClientStatus.ConnectionLost -> {
                            updateConnectionState(false, "Disconnected")
                        }
                        else -> {
                            updateConnectionState(false, "Error: ${throwable?.message ?: status.name}")
                        }
                    }
                }
            } catch (e: Exception) {
                Log.e("AwsIotClient", "Connection error", e)
                updateConnectionState(false, "Error: ${e.message ?: "Unknown"}")
            }
        }
    }

    fun disconnect() {
        ioExecutor.execute {
            try {
                mqttManager.disconnect()
            } catch (_: Exception) {
                // Ignore disconnect errors.
            }
        }
    }

    fun publishEngineState(isOn: Boolean) {
        ioExecutor.execute {
            val payload = """{"device":"${IotConfig.THING_NAME}","state":"${if (isOn) "ON" else "OFF"}"}"""
            try {
                mqttManager.publishString(payload, IotConfig.TOPIC, IotConfig.QOS)
                updateLastState(if (isOn) EngineState.ON else EngineState.OFF)
            } catch (e: Exception) {
                Log.e("AwsIotClient", "Publish error", e)
                updateConnectionState(isConnected, "Publish error: ${e.message ?: "Unknown"}")
            }
        }
    }

    private fun prepareKeyStore(): java.security.KeyStore {
        val keystoreDir = context.filesDir.absolutePath
        val keystoreFile = File(keystoreDir, IotConfig.KEYSTORE_FILE)
        if (!keystoreFile.exists()) {
            val certPem = context.assets.open(IotConfig.CERT_ASSET_PATH)
                .bufferedReader()
                .use { it.readText() }
            val privateKeyPem = context.assets.open(IotConfig.PRIVATE_KEY_ASSET_PATH)
                .bufferedReader()
                .use { it.readText() }
            AWSIotKeystoreHelper.saveCertificateAndPrivateKey(
                IotConfig.KEY_ALIAS,
                certPem,
                privateKeyPem,
                keystoreDir,
                IotConfig.KEYSTORE_FILE,
                IotConfig.KEYSTORE_PASSWORD
            )
        }

        return AWSIotKeystoreHelper.getIotKeystore(
            IotConfig.KEY_ALIAS,
            keystoreDir,
            IotConfig.KEYSTORE_FILE,
            IotConfig.KEYSTORE_PASSWORD
        )
    }

    private fun updateConnectionState(connected: Boolean, status: String) {
        mainHandler.post {
            isConnected = connected
            connectionStatus = status
        }
    }

    private fun updateLastState(state: EngineState) {
        mainHandler.post {
            lastState = state
            prefs.edit().putString("last_state", state.name).apply()
        }
    }

    private fun loadLastState(): EngineState? {
        val stored = prefs.getString("last_state", null) ?: return null
        return runCatching { EngineState.valueOf(stored) }.getOrNull()
    }

    private fun loadOrCreateClientId(context: Context): String {
        val prefs = context.getSharedPreferences("iot_prefs", Context.MODE_PRIVATE)
        val existing = prefs.getString("client_id", null)
        if (!existing.isNullOrBlank()) return existing
        val newId = "bikeengine-watch-${UUID.randomUUID()}"
        prefs.edit().putString("client_id", newId).apply()
        return newId
    }

}
