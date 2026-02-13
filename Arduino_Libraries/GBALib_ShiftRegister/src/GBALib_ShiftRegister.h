/*
  GBALib_ShiftRegister.h - Shift Register 74HC595N Management Library
  Copyright (c) 2024 Graziano Blasilli.

  This library provides a simple interface to control a 74HC595N shift register.
  It allows turning specific bits on or off, toggling bits, and clearing the register.
  The library simplifies interaction with the shift register for various Arduino projects.
*/

#ifndef GBALib_ShiftRegister
#define GBALib_ShiftRegister

#include <Arduino.h>

/**
 * ShiftRegister class for controlling a 74HC595N shift register.
 * Allows turning specific bits on or off, toggling bits, and clearing the register.
 */
class ShiftRegister {
  private:
    uint8_t dataPin;  // Pin connected to the data input of the shift register
    uint8_t clockPin; // Pin connected to the clock input of the shift register
    uint8_t latchPin; // Pin connected to the latch input of the shift register
    byte state;       // Current state of the shift register

    /**
     * Writes a byte value to the shift register.
     * 
     * @param value The byte value to write to the shift register.
     */
    void write(byte value);

  public:
    /**
     * Constructor to initialize the ShiftRegister object and set pin modes.
     * 
     * @param dataPin  The data pin number.
     * @param latchPin The latch pin number.
     * @param clockPin The clock pin number.
     */
    ShiftRegister(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin);

    /**
     * Turns on the specified bit in the shift register.
     * 
     * @param bit The bit to turn on (0-7).
     */
    void on(uint8_t bit);

    /**
     * Turns off the specified bit in the shift register.
     * 
     * @param bit The bit to turn off (0-7).
     */
    void off(uint8_t bit);

    /**
     * Toggles the specified bit in the shift register.
     * 
     * @param bit The bit to toggle (0-7).
     */
    void toggle(uint8_t bit);

    /**
     * Clears all bits in the shift register.
     */
    void clear();
};

#endif
