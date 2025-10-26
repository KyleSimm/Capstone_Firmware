/* 
 * File:   pwm_driver.h
 * Author: School Coding
 *
 * Created on October 17, 2025, 2:08 PM
 */

#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PWM_1 = 1,
    PWM_2 = 2,
    PWM_3 = 3
} PWM_Channel;

void setPWM_Cycle(PWM_Channel channel, uint16_t val);
void setPWM_Phase(PWM_Channel channel, uint16_t val);

#ifdef __cplusplus
}
#endif

#endif /* PWM_DRIVER_H */
