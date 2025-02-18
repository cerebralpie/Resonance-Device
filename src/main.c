/*
 * File:   main.c
 * Author: eduardo
 *
 * Created on 14. Februar 2025, 21:32
 */

#include "mcuSetup.h"
#include <xc.h>

void main(void) {
    PR2      = 0xFF;    // 0xFF TIMER2 period (full count)
    CCPR1L  &= 0x80;    // 0b10000000 duty-cycle MSB
    TRISC   &= 0xFB;    // Clear RC2 pin (set as output)
    T2CON   &= 0x05;    // Set TMR2ON to HIGH, set prescaler to 4
    CCP1CON &= 0x0F;    // PWM mode ON (CCP1 pin), 0b00 duty-cycle LSB
    return;
}
