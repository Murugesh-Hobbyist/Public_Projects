package com.twinbot.touchcounter

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.Canvas
import androidx.compose.animation.animateColorAsState
import androidx.compose.animation.core.animateFloatAsState
import androidx.compose.animation.core.tween
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.scale
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.StrokeCap
import androidx.compose.ui.graphics.drawscope.Stroke
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.wear.compose.material3.Button
import androidx.wear.compose.material3.ButtonDefaults
import androidx.wear.compose.material3.MaterialTheme
import androidx.wear.compose.material3.Text

class MainActivity : ComponentActivity() {
    private lateinit var iotClient: AwsIotClient

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        iotClient = AwsIotClient(this)
        iotClient.connect()
        setContent { WearApp(iotClient) }
    }

    override fun onDestroy() {
        iotClient.disconnect()
        super.onDestroy()
    }
}

@Composable
private fun WearApp(iotClient: AwsIotClient) {
    MaterialTheme { BikeEngineScreen(iotClient) }
}

@Composable
private fun BikeEngineScreen(iotClient: AwsIotClient) {
    Box(
        modifier = Modifier
            .fillMaxSize(),
        contentAlignment = Alignment.Center
    ) {
        Canvas(modifier = Modifier.fillMaxSize()) {
            val strokeWidth = 8.dp.toPx()
            val stroke = Stroke(width = strokeWidth, cap = StrokeCap.Round)
            val radius = (size.minDimension / 2f) - (strokeWidth / 2f)
            drawCircle(
                brush = Brush.sweepGradient(
                    colors = listOf(
                        Color(0xFF2DD4BF),
                        Color(0xFF60A5FA),
                        Color(0xFF34D399),
                        Color(0xFF2DD4BF)
                    )
                ),
                radius = radius,
                style = stroke,
                center = Offset(size.width / 2f, size.height / 2f)
            )
        }

        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(18.dp),
            verticalArrangement = Arrangement.Center,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
        Text(
            text = "Hey Murugesh!",
            style = MaterialTheme.typography.titleSmall,
            textAlign = TextAlign.Center
        )
        Spacer(modifier = Modifier.height(6.dp))
        Text(
            text = "Bike Engine",
            style = MaterialTheme.typography.titleMedium,
            textAlign = TextAlign.Center
        )
        Spacer(modifier = Modifier.height(6.dp))
        Text(
            text = iotClient.connectionStatus,
            style = MaterialTheme.typography.labelSmall,
            textAlign = TextAlign.Center
        )
        Spacer(modifier = Modifier.height(12.dp))
            val onSelected = iotClient.lastState == EngineState.ON
            val offSelected = iotClient.lastState == EngineState.OFF
            val onScale = animateFloatAsState(if (onSelected) 1.08f else 1f, tween(180))
            val offScale = animateFloatAsState(if (offSelected) 1.08f else 1f, tween(180))
            val onColor = animateColorAsState(
                if (onSelected) Color(0xFF16A34A) else Color(0xFF1F2937),
                tween(180)
            )
            val offColor = animateColorAsState(
                if (offSelected) Color(0xFFDC2626) else Color(0xFF1F2937),
                tween(180)
            )

            Row(
                horizontalArrangement = Arrangement.spacedBy(12.dp),
                verticalAlignment = Alignment.CenterVertically
            ) {
                Button(
                    onClick = { iotClient.publishEngineState(true) },
                    enabled = iotClient.isConnected,
                    colors = ButtonDefaults.buttonColors(containerColor = onColor.value),
                    modifier = Modifier.scale(onScale.value)
                ) {
                    Text("ON")
                }
                Button(
                    onClick = { iotClient.publishEngineState(false) },
                    enabled = iotClient.isConnected,
                    colors = ButtonDefaults.buttonColors(containerColor = offColor.value),
                    modifier = Modifier.scale(offScale.value)
                ) {
                    Text("OFF")
                }
            }
        Spacer(modifier = Modifier.height(10.dp))
            if (!iotClient.isConnected) {
                Text(
                    text = "Waiting for AWS IoT...",
                    style = MaterialTheme.typography.labelSmall,
                    textAlign = TextAlign.Center
                )
            }
        }
    }
}
