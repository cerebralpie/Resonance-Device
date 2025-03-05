/* 
 * File:   mcuSetup.c
 * Author: eduardo
 *
 * Created on 18. Februar 2025, 09:48
 */

#include "mcuBase.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void I2C_Initialize() {
    TRISC3 = 1; // Set RC3 (SCL) as input
    TRISC4 = 1; // Set RC4 (SDA) as input
    SSPCON = 0b00101000; // Enable MSSP in Master mode
    SSPCON2 = 0x00; // Reset SSPCON2 register
    SSPADD = ((_XTAL_FREQ / 4) / I2C_BAUD_RATE) - 1; // Set clock frequency
    SSPSTAT = 0x80; // Slew rate control disabled for standard speed mode
}

void I2C_Start() {
    SEN = 1; // Initiate Start condition
    while(SEN); // Wait for Start condition to complete
}

void I2C_Stop() {
    PEN = 1; // Initiate Stop condition
    while(PEN); // Wait for Stop condition to complete
}

void I2C_Write(uint8_t data) {
    SSPBUF = data; // Load data into buffer
    while(!SSPIF); // Wait for transmission to complete
    SSPIF = 0; // Clear interrupt flag
}

void initSystem() {
    I2C_Initialize();
}
