#include <xc.h>
#include "vfdControlLoop.h"
#include "pwm_driver.h"
#include <stdint.h>

// {index, stepSize, direction}
static PWM_State pwm_A = {0,0,1};                      // 0   phase shift
static PWM_State pwm_B = {table_Size / 3, 0, 1};       // 120 phase shift
static PWM_State pwm_C = {2 * table_Size / 3, 0, 1};   // 240 Phase shift

void vfd_Init(void){
    float initialFreq = 5.0f;
    
    vfd_SetFrequency(initialFreq);
}


//Frequency Control Logic
void vfd_SetFrequency(float freq){
    pwm_UpdateStep(&pwm_A,freq);
    pwm_UpdateStep(&pwm_B,freq);
    pwm_UpdateStep(&pwm_C,freq);
}

void vfd_SetDirection(Direction direct){
    pwm_A.direction = direct;
    pwm_B.direction = direct;
    pwm_C.direction = direct;
}


//Control Loop Logic
void vfd_Update(void){
    uint16_t valA = pwm_nextVal(&pwm_A);
    uint16_t valB = pwm_nextVal(&pwm_B);
    uint16_t valC = pwm_nextVal(&pwm_C);

    setPWM_channel('A',valA);
    setPWM_channel('B',valB);
    setPWM_channel('C',valC);
}

//Maybe Make SPI Channel Connection here? 