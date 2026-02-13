
# GBALib_ShiftRegister

![Arduino Logo](./extras/ArduinoCommunityLogo.png)

**GBALib_ShiftRegister** is a lightweight Arduino library for managing the **74HC595N Shift Register**. This library provides a simple and intuitive interface to control the outputs of a shift register, allowing you to manipulate individual bits, toggle them, or clear the entire register. 

## Features

- **Turn on/off specific bits**: Control each output pin of the shift register independently.
- **Toggle bits**: Easily invert the state of any bit.
- **Clear all bits**: Reset all outputs to `LOW`.
- **Efficient state management**: The internal state is tracked to minimize unnecessary operations.

## Installation

The library is included in the **Arduino Library Manager**. You can install it either by using the Library Manager or manually by following the steps below.

1. Download or clone this repository:
   ```bash
   git clone https://github.com/<your-repo-name>/GBALib_ShiftRegister.git
   ```
2. Copy the `GBALib_ShiftRegister` folder into your Arduino `libraries` directory.
3. Restart the Arduino IDE to refresh the library index.

## API Reference

### Constructor

```cpp
ShiftRegister(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin);
```

- **dataPin**: The pin connected to the data input of the shift register.
- **latchPin**: The pin connected to the latch input of the shift register.
- **clockPin**: The pin connected to the clock input of the shift register.

### Methods

#### `on(uint8_t bit)`
Turns on a specific bit in the shift register.

- **bit**: The bit to turn on (0-7).

#### `off(uint8_t bit)`
Turns off a specific bit in the shift register.

- **bit**: The bit to turn off (0-7).

#### `toggle(uint8_t bit)`
Toggles the state of a specific bit in the shift register.

- **bit**: The bit to toggle (0-7).

#### `clear()`
Clears all bits in the shift register, resetting all outputs to `LOW`.

## Example Usage

Here’s an example of how to use the library:

```cpp
#include <GBALib_ShiftRegister.h>

// Initialize a ShiftRegister object with dataPin=2, latchPin=3, clockPin=4
ShiftRegister sr(2, 3, 4);

void setup() {
  sr.clear(); // Reset all outputs
}

void loop() {
  // Sequentially turn on and off each bit
  for (int i = 0; i < 8; i++) {
    sr.on(i);
    delay(500);
    sr.off(i);
    delay(500);
  }
}
```

## Compatibility

This library is compatible with the **74HC595N Shift Register** and supports the following architectures:


## License

This library is licensed under the **GNU License**. See the `LICENSE` file for details.

