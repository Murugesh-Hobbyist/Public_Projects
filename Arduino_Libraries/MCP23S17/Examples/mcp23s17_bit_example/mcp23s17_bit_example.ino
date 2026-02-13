

#include <SPI.h>              // We use this library, so it must be called here.
#include <MCP23S17.h>         // Here is the new class to make using the MCP23S17 easy.

MCP outputchip(0, 10);  

void setup() {
Serial.begin(115200);
  outputchip.begin();
  for (int i = 1; i <= 16; i++) {  
    outputchip.pinMode(i, LOW);      // Use bit-write mode to Set all of the current pin on outputchip to be an output
  }
}

void loop() {
  for (int i = 1; i <=16; i++) {  
     outputchip.digitalWrite(i, HIGH); 
      Serial.println(i);
  }
  delay(500);
  for (int i = 1; i <=16; i++) {  
     outputchip.digitalWrite(i, LOW); 
      Serial.println(i);
  }
  delay(500);
}
