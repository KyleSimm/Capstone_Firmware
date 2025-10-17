/* 
 * File:   pwm_lookup.h
 * Author: Kyle Simmons
 *
 * Created on October 16, 2025, 8:40 PM
 */

#ifndef PWM_LOOKUP_H
#define	PWM_LOOKUP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

#define table_Size 256
#define pwm_Max 2000

typedef enum { FORWARD = 1, REVERSE = -1 } Direction;

typedef struct {
    uint16_t index;
    float step_size;
    Direction direction;
} PWM_State;

uint16_t pwm_NextVal(PWM_State *state);
void pwm_UpdateStep(PWM_State *state, float frequency);



#ifdef	__cplusplus
}
#endif

#endif	/* PWM_LOOKUP_H */

