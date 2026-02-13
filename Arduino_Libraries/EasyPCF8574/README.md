# EasyPCF8574
A simple PCF8574 control

16.04.2021
Changes by: 
David-2D3FE9

WriteBit method added to allow to write a bit from a parameter source (e.g. from another function).

startI2C will now push the initial value to PCF8574,
otherwise the initial value is useless until the first set/reset/invert.

The example received the new method.
Because the loop will repeat forever I added a "====>" to the cycle begin in order to make this more visual in serial output
The serial output display values in BIN format witch is more readable

M examples/usage.ino (39)
M library.json (2)
M library.properties (2)
M src/EasyPCF8574.cpp (14)
M src/EasyPCF8574.h (5)
