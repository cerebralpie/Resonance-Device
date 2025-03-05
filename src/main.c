/*
 * File:   main.c
 * Author: eduardo
 *
 * Created on 14. Februar 2025, 21:32
 */

#include "mcuBase.h"
#include "resonanceAudio.h"
#include <xc.h>

int main(void) {
    //initSystem();

    size_t numSamples = sizeof(SINE_WAVE) / sizeof(SINE_WAVE[0]); 
    generateAudio(1000, SINE_WAVE, numSamples);
    
    //while (1) {
    //    delay_one_second();
    //    PORTD |= 0b00000100;
    //    delay_one_second();
    //    PORTD   &= 0b11111011;    
    //}
    
    return 0;
}





