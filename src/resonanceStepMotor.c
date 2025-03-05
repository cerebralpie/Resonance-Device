#include "resonanceStepMotor.h"
#include <stdint.h>

uint8_t stepDelay = 10; // Default delay between steps in ms

void stepperInitialize() {
    TRISDbits.TRISD0 = 0; // RD0 pin as output for DIR
    TRISDbits.TRISD1 = 0; // RD1 pin as output for STP
    TRISCbits.TRISC1 = 0; // RC1 pin as output for RST
    TRISCbits.TRISC2 = 0; // RC2 pin as output for SLP

    PORTDbits.RD0 = 0; // Initialize DIR as LOW
    PORTDbits.RD1 = 0; // Initialize STP as LOW
    PORTCbits.RC1 = 0; // Initialize RST as LOW, reset active
    PORTCbits.RC2 = 0; // Initialize SLP as LOW, sleep active

    __delay_ms(10);
    PORTCbits.RC1 = 1; // Release RST
} 

void stepperEnable() {
    PORTCbits.RC2 = 1; // Wake up DRV8825 driver
    __delay_ms(2);
}

void stepperDisable() {
    PORTCbits.RC2 = 0; // Put DRV8825 driver to sleep
}

void stepperStep(uint8_t steps, Direction direction) {
    switch (direction) {
        case CLOCKWISE:
            PORTDbits.RD0 = 0; // Set DIR as CLOCKWISE
            break;

        case COUNTERCLOCKWISE:
            PORTDbits.RD0 = 1; // Set DIR as COUNTERCLOCKWISE
            break
        
        default:
            PORTDbits.RD0 = 0; // Unknown command, set DIR as CLOCKWISE
    }

    for (uint8_t i = 0; i < steps; ++i) {
        PORTDbits.RD1 = 1; // Set STP as HIGH
        __delay_ms(1);
        PORTDbits.RD1 = 0; // Return STP to LOW 
        __delay_ms(stepDelay);
    }
}

void stepperSetSpeed(uint8_t speed) {
    uint8_t speedPercentage = (speed*100)/255;
    // TO-DO - NOT PRIORITIZED
}