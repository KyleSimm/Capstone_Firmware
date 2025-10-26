/*
 * File:   vfd_control_loop.h
 * Author: Kyle Simmons
 *
 * Created on October 16, 2025, 8:41 PM
 */

#ifndef VFD_CONTROL_LOOP_H
#define	VFD_CONTROL_LOOP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "pwm_driver.h"     // must come BEFORE pwm_control functions
#include "pwm_Lookup.h"
#include <stdint.h>
#include <math.h>

// Test pin macros
#define TEST_PIN_LAT LATDbits.LATD7
#define TEST_PIN_TRIS TRISDbits.TRISD7
    
// Initialize VFD control
void vfd_Init(void);

// Update the PWM step size for each phase according to new frequency
void vfd_SetFrequency(float freq);

// Set direction (FORWARD/REVERSE)
void vfd_SetDirection(Direction direct);

// Called periodically (e.g., in interrupt) to update the control loop
void vfd_Update(float newFreq);

void MyPWMInterrupt(void);

void sendDebugSample(uint8_t pin_state, uint16_t dutyA, uint16_t dutyB, uint16_t dutyC);


#ifdef	__cplusplus
}
#endif

#endif	/* VFD_CONTROL_LOOP_H */

