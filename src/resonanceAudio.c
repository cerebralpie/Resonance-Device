#include "mcuBase.h"
#include "resonanceAudio.h"
#include <stdint.h>

void MCP4725SetVoltage(uint16_t value) {
    uint8_t msb = value >> 4; // Most significant bits
    uint8_t lsb = (value & 0x0F) << 4; // Least significant bits

    I2C_Start();
    I2C_Write(0x60); // MCP4725 address with write bit (default is 0x60)
    I2C_Write(msb); // Send MSB
    I2C_Write(lsb); // Send LSB
    I2C_Stop();
}

void generateAudio(uint16_t frequency, const uint16_t* sineWave, uint8_t samples) {
    uint8_t instructionsPerSec = _XTAL_FREQ / 4;
    float period = 1 / frequency;
    uint16_t numInstructions = instructionsPerSec * period;
    
    while (1) {
            for (uint16_t i = 0; i < samples; ++i) {
                MCP4725SetVoltage(*(sineWave + j));
                for (uint16_t j = 0; j < numInstructions; ++j) {
                    __asm("nop"); // Do nothing
                }
            }
    }
}

