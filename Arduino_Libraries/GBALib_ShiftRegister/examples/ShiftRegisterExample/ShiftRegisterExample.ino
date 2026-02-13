#include <GBALib_ShiftRegister.h>

// Create a ShiftRegister object with dataPin=2, latchPin=3, clockPin=4
ShiftRegister sr(2, 3, 4);

void setup() {
  sr.clear(); // Clear all outputs on startup
  

}

void loop() {
  // Sequentially turn on and off each bit in a loop
  for (int i = 0; i < 8; i++) {
    sr.on(i);
    delay(250);
    sr.off(i);
    delay(250);
  }

  delay(1000);

  // Turn on bit 0 (connected to Q0 on 74HC595N)
  sr.on(0);
  delay(1000);

  // Turn off bit 0
  sr.off(0);
  delay(1000);

  // Toggle bit 1 twice
  sr.toggle(1);
  delay(1000);
  sr.toggle(1);
  delay(1000);

  // Turn on all bits one by one
  for (int i = 0; i < 8; i++) {
    sr.on(i);
    delay(500);
  }

  // Clear all bits
  sr.clear();
}
