package com.twinbot.touchcounter

import com.amazonaws.mobileconnectors.iot.AWSIotMqttQos

object IotConfig {
    // TODO: Replace with your AWS IoT Core endpoint (from Settings > Endpoint).
    const val AWS_IOT_ENDPOINT = "a1xj2prudrcgqr-ats.iot.ap-south-1.amazonaws.com"

    // TODO: Replace with your Thing name (example: BikeEngine).
    const val THING_NAME = "BikeEngine"

    // TODO: Update to the topic your device listens to.
    const val TOPIC = "bikeengine/control"

    const val CERT_ASSET_PATH = "certs/device.pem.crt"
    const val PRIVATE_KEY_ASSET_PATH = "certs/private.pem.key"

    const val KEYSTORE_FILE = "iot_keystore.bks"
    const val KEYSTORE_PASSWORD = "changeit"
    const val KEY_ALIAS = "iot_key"

    const val KEEP_ALIVE_SECONDS = 60
    val QOS = AWSIotMqttQos.QOS0
}
