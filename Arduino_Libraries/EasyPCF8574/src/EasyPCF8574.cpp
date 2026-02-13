#include "EasyPCF8574.h"
//
EasyPCF8574::EasyPCF8574(uint8_t pcf_addr, uint8_t initial_value){
    this->pcf_address    = pcf_addr;
    this->started        = false;
    this->pcf_last_value = initial_value;
}

void EasyPCF8574::setPCFaddress(uint8_t addr){
    this->pcf_address = addr;
}

void EasyPCF8574::setFullValue(uint8_t value){
    if (this->started){
        Wire.beginTransmission(this->pcf_address);
        Wire.write(value);
        Wire.endTransmission();
    }
}

void EasyPCF8574::setFullValue(uint8_t value, uint8_t pcf_addr){
    if (this->started){
        Wire.beginTransmission(pcf_addr);
        Wire.write(value);
        Wire.endTransmission();
    }
}

void EasyPCF8574::setInvertBit(uint8_t bit_to_change){
    if (!this->started) return;

    this->pcf_last_value = pcf_last_value^(1<<bit_to_change);
    this->setFullValue(this->pcf_last_value);
}

void EasyPCF8574::setInvertBit(uint8_t bit_to_change, uint8_t pcf_addr){
    this->pcf_last_value = pcf_last_value^(1<<bit_to_change);
    this->setFullValue(this->pcf_last_value, pcf_addr);
}

void EasyPCF8574::setDownBit(uint8_t bit_to_change){
    this->pcf_last_value = pcf_last_value&~(1<<bit_to_change);
    this->setFullValue(this->pcf_last_value);
}

void EasyPCF8574::setDownBit(uint8_t bit_to_change, uint8_t pcf_addr){
    this->pcf_last_value = pcf_last_value&~(1<<bit_to_change);
    this->setFullValue(this->pcf_last_value, pcf_addr);
}

void EasyPCF8574::setUpBit(uint8_t bit_to_change){
    this->pcf_last_value = pcf_last_value|(1<<bit_to_change);
    this->setFullValue(this->pcf_last_value);
}

void EasyPCF8574::setUpBit(uint8_t bit_to_change, uint8_t pcf_addr){
    this->pcf_last_value = pcf_last_value|(1<<bit_to_change);
    this->setFullValue(this->pcf_last_value, pcf_addr);
}

void EasyPCF8574::WriteBit(bool value_to_write, uint8_t bit_to_change){
    this->pcf_last_value = pcf_last_value ^(-value_to_write ^ pcf_last_value) & (1<<bit_to_change);
    this->setFullValue(this->pcf_last_value);
}

void EasyPCF8574::WriteBit(bool value_to_write, uint8_t bit_to_change, uint8_t pcf_addr){
    this->pcf_last_value = pcf_last_value ^(-value_to_write ^ pcf_last_value) & (1<<bit_to_change);
    this->setFullValue(this->pcf_last_value, pcf_addr);
}

uint8_t EasyPCF8574::getPCFValue(){
    Wire.requestFrom(this->pcf_address,1);
    if (Wire.available()){
         return Wire.read();
    }
    else{
        return 0;
    }
}

uint8_t EasyPCF8574::getPCFValue(uint8_t pcf_addr){
    Wire.requestFrom(pcf_addr,1);
    if (Wire.available()){
         return Wire.read();
    }
    else{
        return 0;
    }
}

uint8_t EasyPCF8574::getBitValue(uint8_t bit_position){
    Wire.requestFrom(this->pcf_address,1);
    if (Wire.available()){
        this->pcf_last_value = Wire.read();
    }
    return this->pcf_last_value&(1<<bit_position);
}

uint8_t EasyPCF8574::getBitValue(uint8_t bit_position, uint8_t pcf_addr){
    Wire.requestFrom(pcf_addr,1);
    if (Wire.available()){
        this->pcf_last_value = Wire.read();
    }
    return this->pcf_last_value&(1<<bit_position);
}

bool EasyPCF8574::startI2C(uint8_t sda_pin, uint8_t scl_pin){
    if (Wire.begin(sda_pin,scl_pin)){
        this->started = true;
        this->setFullValue(this->pcf_last_value);
        return true;
    }
}

bool EasyPCF8574::startI2C(){
    if (Wire.begin()){
        this->started = true;
        this->setFullValue(this->pcf_last_value);
        return true;
    }
}
