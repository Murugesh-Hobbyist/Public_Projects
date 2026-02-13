#include <Arduino.h>
#include <Wire.h>
//
/*
PCF8574 handler - by: Djames Suhanko <djames.suhanko@gmail.com> - 10.01.2020 v.1.0
*/
class EasyPCF8574{
 public:
    bool started;

    //! save last value read.
    uint8_t pcf_last_value;

    EasyPCF8574(uint8_t pcf_addr, uint8_t initial_value);
    //! just a default address value.
    uint8_t pcf_address;

    //! change default PCF8574 address to a new one.
    void setPCFaddress(uint8_t addr);

    //! No matter the old value, this function will ignore it.
    void setFullValue(uint8_t value);
    //! Overriding method, passing pcf_address if more than one is connected
    void setFullValue(uint8_t value, uint8_t pcf_addr);

    //! invert a bit, no matter if actual value is 0 or 1.
    void setInvertBit(uint8_t bit_to_change);
    //! Overriding method, passing pcf_address if more than one is connected
    void setInvertBit(uint8_t bit_to_change, uint8_t pcf_addr);

    //! Turn bit value 0, no metter if bit already was 0.
    void setDownBit(uint8_t bit_to_change);
    //! Overriding method, passing pcf_address if more than one is connected
    void setDownBit(uint8_t bit_to_change, uint8_t pcf_addr);

    //! Turn bit value 1, no matter if bit already was 1.
    void setUpBit(uint8_t bit_to_change);
    //! Overriding method, passing pcf_address if more than one is connected
    void setUpBit(uint8_t bit_to_change, uint8_t pcf_addr);

    //! Direct write bit, no matter of actual state
    void WriteBit(bool value_to_write, uint8_t bit_to_change);
    //! Overriding method, passing pcf_address if more than one is connected
    void WriteBit(bool value_to_write, uint8_t bit_to_change, uint8_t pcf_addr);

    //! Gets PCF8574 actual value.
    uint8_t getPCFValue();
    //! Overloaded (or 'Overriding'?) method, passing pcf_address if more than one is connected
    uint8_t getPCFValue(uint8_t pcf_addr);

    //! Gets a specific bit value
    uint8_t getBitValue(uint8_t bit_position);
    //! Overriding method, passing pcf_address if more than one is connected
    uint8_t getBitValue(uint8_t bit_position, uint8_t pcf_addr);

    //! Starts wire with specific pins and returns status.
    bool startI2C(uint8_t sda_pin, uint8_t scl_pin);
    //! Overriding method, passing pcf_address if more than one is connected
    bool startI2C();

    //! Prints help on Serial.
    void help(); 
};
