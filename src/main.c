/*
 * File:   main.c
 * Author: eduardo
 *
 * Created on 14. Februar 2025, 21:32
 */

#include "mcuSetup.h"
#include <xc.h>

void delay_one_second();
void I2C_Initialize();
void I2C_Start();
void I2C_Stop();
void I2C_Write(unsigned char data);
void MCP4725_SetVoltage(unsigned int value);

void main(void) {
    PR2      = 0xFF;    // 0xFF TIMER2 period (full count)
    CCPR1L  &= 0x80;    // 0b10000000 duty-cycle MSB
    TRISC   &= 0xFB;    // Clear RC2 pin (set as output)
    T2CON   &= 0x05;    // Set TMR2ON to HIGH, set prescaler to 4
    CCP1CON &= 0x0F;    // PWM mode ON (CCP1 pin), 0b00 duty-cycle LSB
    
    TRISD   &= 0b11111011; 
    PORTD   &= 0b11111011;
    
     unsigned int value;

    I2C_Initialize(); // Initialize I2C

    while(1) {
        for(value = 0; value < 4096; value++) { // Sweep through all DAC values
            MCP4725_SetVoltage(value);
            __delay_ms(10); // Small delay between updates
        }
    }
    
    //while (1) {
    //    delay_one_second();
    //    PORTD |= 0b00000100;
    //    delay_one_second();
    //    PORTD   &= 0b11111011;    
    //}
    
    return;
}

void delay_one_second() {
    int i;
    unsigned long j;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 125000; j++) {
            // Each iteration takes 4 machine cycles
            __asm("nop"); // Optional: Insert a "nop" (no operation) to ensure consistent timing
    
        }
        
    }
}

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

void I2C_Write(unsigned char data) {
    SSPBUF = data; // Load data into buffer
    while(!SSPIF); // Wait for transmission to complete
    SSPIF = 0; // Clear interrupt flag
}

void MCP4725_SetVoltage(unsigned int value) {
    unsigned char msb = value >> 4; // Most significant bits
    unsigned char lsb = (value & 0x0F) << 4; // Least significant bits

    I2C_Start();
    I2C_Write(0x60); // MCP4725 address with write bit (default is 0x60)
    I2C_Write(msb); // Send MSB
    I2C_Write(lsb); // Send LSB
    I2C_Stop();
}


