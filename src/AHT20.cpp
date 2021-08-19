#include "AHT20.h"

#define AHT20_ADDR 0x38

AHT20::AHT20() {

}

bool AHT20::begin() {
    Wire.beginTransmission(AHT20_ADDR);
    Wire.write((uint8_t*)"\xBE", 1);
    return Wire.endTransmission() == 0;
}

bool AHT20::read(float* t, float* h) {
    uint8_t data[6];
    Wire.beginTransmission(AHT20_ADDR);
    Wire.write((uint8_t*)"\xAC\x33\x00", 3);
    if (Wire.endTransmission() != 0) {
        return false;
    }

    delay(100);

    if (Wire.requestFrom(AHT20_ADDR, 6) != 6) {
        return false;
    }

    Wire.readBytes(data, 6);

    if ((data[0] & 0x08) == 0) {
        this->begin();
        delay(100);
        return false;
    }

    if ((data[0] & 0x80) != 0) {
        return false;
    }
    
    *h = (uint32_t)(((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (((uint32_t)data[3] & 0xF0) >> 4)) / 1048576.0 * 100.0;
    *t = (uint32_t)((((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | (uint32_t)data[5]) / 1048576.0 * 200.0 - 50.0;

    return true;
}

AHT20 aht;
