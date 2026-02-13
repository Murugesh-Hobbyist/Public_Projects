#include "SoftwareSerial.h"
SoftwareSerial aaah;
#define aaa aaah

void setup() {
	Serial.begin(115200);
	aaa.begin(115200, SWSERIAL_8N1, 7, 8);
}

void loop() {
	aaa.println("hello 846541");
delay(100);
}
