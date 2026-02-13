/*
  GBALib_ShiftRegister.cpp - Shift Register 74HC595N Management Library
  Copyright (c) 2024 Graziano Blasilli.

  This library provides a simple interface to control a 74HC595N shift register.
  It allows turning specific bits on or off, toggling bits, and clearing the register.
  The library simplifies interaction with the shift register for various Arduino projects.
*/

#include "GBALib_ShiftRegister.h"

// Constructor to initialize the ShiftRegister object and set pin modes
ShiftRegister::ShiftRegister(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin)
  : dataPin(dataPin), latchPin(latchPin), clockPin(clockPin), state(0) {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

// Private method to write a byte value to the shift register
void ShiftRegister::write(byte value) {
  this->state = value;  // Update internal state
  digitalWrite(this->latchPin, LOW);  // Bring latch low to prepare for data transmission
  shiftOut(this->dataPin, this->clockPin, MSBFIRST, value);  // Shift out the value
  digitalWrite(this->latchPin, HIGH);  // Bring latch high to lock the data
}

// Turns on a specific bit in the shift register
void ShiftRegister::on(uint8_t bit) {
  if (bit > 7) return; // Ignore invalid bits
  this->state |= (1 << bit); // Set the specified bit
  this->write(this->state);  // Write the updated state to the shift register
}

// Turns off a specific bit in the shift register
void ShiftRegister::off(uint8_t bit) {
  if (bit > 7) return; // Ignore invalid bits
  this->state &= ~(1 << bit); // Clear the specified bit
  this->write(this->state);   // Write the updated state to the shift register
}

// Toggles a specific bit in the shift register
void ShiftRegister::toggle(uint8_t bit) {
  if (bit > 7) return; // Ignore invalid bits
  this->state ^= (1 << bit); // Toggle the specified bit
  this->write(this->state);  // Write the updated state to the shift register
}

// Clears all bits in the shift register
void ShiftRegister::clear() {
  this->state = 0;          // Reset state
  this->write(this->state); // Write the cleared state to the shift register
}
