/* 
 * File:   resonanceStepMotor.h
 * Author: eduardo
 *
 * Created on February 24, 2025, 7:08 PM
 */

#ifndef RESONANCESTEPMOTOR_H
#define	RESONANCESTEPMOTOR_H

void stepperInitialize();
void stepperEnable();
void stepperDisable();
void stepperStep(uint8_t steps, Direction direction);
void stepperSetSpeed(uint8_t speed);

enum Direction {
    CLOCKWISE = 0,
    COUNTERCLOCKWISE = 1
};


#endif	/* RESONANCESTEPMOTOR_H */

