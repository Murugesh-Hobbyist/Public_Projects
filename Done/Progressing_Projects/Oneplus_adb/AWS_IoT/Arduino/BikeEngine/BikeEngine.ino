#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Preferences.h>

// ===== WiFi =====
const char* WIFI_SSID = "Speed";
const char* WIFI_PASS = "12344321";
const char* WIFI_FALLBACK1_SSID = "ANNA INCUBATOR";
const char* WIFI_FALLBACK1_PASS = "AIC@networks";
const char* WIFI_FALLBACK2_SSID = "TP-Link_8054";
const char* WIFI_FALLBACK2_PASS = "44124243";

// ===== AWS IoT =====
const char* AWS_ENDPOINT = "a1xj2prudrcgqr-ats.iot.ap-south-1.amazonaws.com";
const int AWS_PORT = 8883;
const char* MQTT_TOPIC = "bikeengine/control";
const char* CLIENT_ID = "BikeEngine-esp32s3";

// ===== GPIO =====
const int ENGINE_PIN = 13;

// ===== Certificates (fill these) =====
// Root CA (AmazonRootCA1.pem)
static const char AWS_ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device certificate (*.pem.crt)
static const char DEVICE_CERT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUcKDe0rSPFnI2+vj1od56Tgl/mn4wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDEzMDEyMzI1
MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANEmQNYjEuPEeJoR/yGi
tlxUZ0ePOX7MHJm2KXQp7Ka4ub6DmXC/vutIHHQHFdn/cePxStePV6pwCigcQ708
7o1kLDNbD5472ZA1wVrOdLuMqVplbTMnqUY7+GfKp7phn57EVQFAS048DtVOXHjo
efHCPNNq65JfJzR/vwC2gtA7+ZUWEFYPfUyvFp8K5vHbJUPDe6T4+WSODgpFXAyY
eXHXb+K6XD3pfm/MKVSoTVLIu7BlT41bPHW1B5Ao/xn5n6j05gudDJpsD0AkJxv9
RpFhbNwcJc/5CW88aRBCSyKV8Od5Pnr9kE3L/dCfq9hcyLlqZ7CsVy3cNaHDxj9J
TAcCAwEAAaNgMF4wHwYDVR0jBBgwFoAU+iY5UGyhCW/Rmg4HjiMC+ffBlMAwHQYD
VR0OBBYEFC5Ef1jLTMD3RTLHDzLQq8TPMmRCMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCaz+L8bFZEJCZHELmNNnrEMU3h
Nw1Clxu+ZMgpMDcTj7PmmBoXKWfeIYWt1cMuRxX7ro0U5cElD1eo7rUrz4uO2N/W
AVVFeNC7S0ODfkuM/kGn8EY+1LHCj17kOaBONjvkJZxTlYfTvIpI3x5qDppatY4a
POvLjcAP+CGDpDvqdsAXgjUlrjRm0BRhnFltLryANslxq/vfSSt1e+zBDZeHlLNw
XzGQUrSeSQY8FekTgmRjSEHjRQfmFRXrX1Z22mMa66N5QxX9tjP0BMbKWSgvUTuO
rtXzMmH3leuAuaussxMyYX9lJ171ReyM250k5uIHyHgVS8Uz7XK1xv9JlsgX
-----END CERTIFICATE-----
)EOF";

// Device private key (*.pem.key)
static const char PRIVATE_KEY[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA0SZA1iMS48R4mhH/IaK2XFRnR485fswcmbYpdCnspri5voOZ
cL++60gcdAcV2f9x4/FK149XqnAKKBxDvTzujWQsM1sPnjvZkDXBWs50u4ypWmVt
MyepRjv4Z8qnumGfnsRVAUBLTjwO1U5ceOh58cI802rrkl8nNH+/ALaC0Dv5lRYQ
Vg99TK8Wnwrm8dslQ8N7pPj5ZI4OCkVcDJh5cddv4rpcPel+b8wpVKhNUsi7sGVP
jVs8dbUHkCj/GfmfqPTmC50MmmwPQCQnG/1GkWFs3Bwlz/kJbzxpEEJLIpXw53k+
ev2QTcv90J+r2FzIuWpnsKxXLdw1ocPGP0lMBwIDAQABAoIBAFT87WXWtMtXQAaj
f4AkhWP5bEp42c07lfekPS4WBzMsZ1YSVdyqHiOvlthTNL7z/Uy59Uao2d/JTWdF
LQWN6AYOiaOIwkzzVxIxtdN3h5naq8qu4nPiDvgaUHOktwmWt+0lLMGoZbFx2Dk3
cX40QbFK07q5fOZqwhykOHJKt9dzevL5+J9Hn+n4MS6EPDhfclH81pRVeez9ZLbn
qJhVMdpWM3Gl9uc94xKl3lbZ+i5coXYz1BNRxM8b/xGcrhmieVE9dc3HzOLVpPxP
YaOzMAJnNZZXEz3spNK2OLo9+JVIHYI2ig2Rj+GxPStZbiwMqFGNJEL41NQJ8Ch6
EkoNLIECgYEA+j6OZI3JlAuIqFFbqGJuFCSfAH4XrdotafmH85SOIN7ru/jR/VJb
lCU+aaLj9WFzqwG9qjqjurUo74B8qUc0R5vJW+XAIU+cZOwNy6NdDKEBoAIbbDmt
rogUJ/IiZUiPPiORTMsoSgfbjtwO4vsW60ui6a8yEc2t3Cix+XVRR0cCgYEA1fW6
sLiNvwT96UYf9SkGAqjkqlvk+WxLueSwr3qqr8lH6VL91Lu7fxB0Q+cYlx158RiT
fpxX25D0swsg85sRhrv2eetJOIQM9+A13mXEYhEkcN7XYlJSrENEZ/zUHJ0aT3/u
3N+82ApFYjGD0kywBCW8cHDhUCme55DyFuI3tUECgYBOHMLD3oJipOsGZ0buG7Ny
tC+xrqpjiSwN3WczgFaRKiR5a2TY5yFQ8AM4ZDE2AjJh2cxDW8SJ3kyl3fyLtn86
LwW+msvLWhdeZVS1EQxVidiBAsdek+6EAVQRWAKmjOyxn9aWGwA7g5JkWIqJDYmM
7vIucZJ2fjZb95P+Y0F4twKBgQCem0hHlKfPAJ5Q/ODX1g9UjWrlNrXoh/Ui2np3
utEo+mbKefEccAYvzTzC0V8TNpCcvwEnjDI825np18gXjc5SOKgf/OEMeic64QRN
1tbbc6W13huAEVKjzEG7bFq402UbpdSl+118MTD594amsJ6SlH66Q5Ni31eihXpQ
qGVvgQKBgBkU1NasB/mcBZqUC/INhKYhfAO3+0eek870Llq2pgW7VYOl4QBfnc6X
FhyHi8UhTIMZHxmwER0eVAf6SgbRoXRZpTCaATK+2ncLJpN6mIQsluTJeAQIg4GA
DztwEIBwbJVN0E+o0gZAppmmTYctzi48oejdX8eO3X7tMJ9DMfUp
-----END RSA PRIVATE KEY-----
)EOF";

WiFiClientSecure net;
PubSubClient client(net);
Preferences prefs;

void setEngineState(bool on, bool persist = true) {
  digitalWrite(ENGINE_PIN, on ? HIGH : LOW);
  if (persist) {
    prefs.putBool("engine_on", on);
  }
  Serial.print("Engine state -> ");
  Serial.println(on ? "ON" : "OFF");
}

void onMessage(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received [");
  Serial.print(topic);
  Serial.print("] ");
  String msg;
  msg.reserve(length + 1);
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.println(msg);

  msg.toUpperCase();
  if (msg.indexOf("\"STATE\":\"ON\"") >= 0 || msg.indexOf("ON") >= 0) {
    setEngineState(true, true);
    Serial.println("Parsed state: ON");
  } else if (msg.indexOf("\"STATE\":\"OFF\"") >= 0 || msg.indexOf("OFF") >= 0) {
    setEngineState(false, true);
    Serial.println("Parsed state: OFF");
  } else {
    Serial.println("Parsed state: UNKNOWN");
  }
}

bool connectWiFiNetwork(const char* ssid, const char* pass, uint32_t timeoutMs) {
  Serial.print("Connecting WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  const uint32_t startMs = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - startMs) < timeoutMs) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected to ");
    Serial.print(ssid);
    Serial.print(". IP: ");
    Serial.println(WiFi.localIP());
    return true;
  }

  Serial.print("WiFi failed for ");
  Serial.println(ssid);
  WiFi.disconnect(true, true);
  delay(300);
  return false;
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    if (connectWiFiNetwork(WIFI_SSID, WIFI_PASS, 12000)) {
      return;
    }
    Serial.println("Trying fallback WiFi #1...");
    if (connectWiFiNetwork(WIFI_FALLBACK1_SSID, WIFI_FALLBACK1_PASS, 12000)) {
      return;
    }
    Serial.println("Trying fallback WiFi #2...");
    if (connectWiFiNetwork(WIFI_FALLBACK2_SSID, WIFI_FALLBACK2_PASS, 12000)) {
      return;
    }
    Serial.println("All WiFi networks failed. Retrying in 2 seconds...");
    delay(2000);
  }
}

void connectAWS() {
  Serial.println("Connecting to AWS IoT...");
  net.setCACert(AWS_ROOT_CA);
  net.setCertificate(DEVICE_CERT);
  net.setPrivateKey(PRIVATE_KEY);

  client.setServer(AWS_ENDPOINT, AWS_PORT);
  client.setCallback(onMessage);

  while (!client.connected()) {
    Serial.print("MQTT connecting as ");
    Serial.println(CLIENT_ID);
    client.connect(CLIENT_ID);
    Serial.print("MQTT state: ");
    Serial.println(client.state());
    delay(500);
  }

  client.subscribe(MQTT_TOPIC);
  Serial.print("Subscribed to: ");
  Serial.println(MQTT_TOPIC);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Booting BikeEngine ESP32-S3...");
  prefs.begin("bikeengine", false);
  pinMode(ENGINE_PIN, OUTPUT);
  const bool savedState = prefs.getBool("engine_on", false);
  Serial.print("Restored last engine state: ");
  Serial.println(savedState ? "ON" : "OFF");
  setEngineState(savedState, false);

  connectWiFi();
  connectAWS();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost. Reconnecting...");
    connectWiFi();
  }
  if (!client.connected()) {
    Serial.println("MQTT disconnected. Reconnecting...");
    connectAWS();
  }
  client.loop();
  delay(10);
}

