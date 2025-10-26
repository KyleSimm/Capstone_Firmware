#include <xc.h>
#include "vfd_Control_Loop.h"
#include <stdint.h>

// {index, stepSize, direction}
static PWM_State pwm_A = {0,.08,1};                      // 0   phase shift
static PWM_State pwm_B = {table_Size / 3, .08, 1};       // 120 phase shift
static PWM_State pwm_C = {2 * table_Size / 3, .08, 1};   // 240 Phase shift

void vfd_Init(void)
{
    init_sine_table();
    
    //PWM Set to 5 Hz
    float initialFreq = 5.0f;
    vfd_SetFrequency(initialFreq); //Also Sets StepSize
    
    
    
    // Configure RD7 as digital output
    TEST_PIN_TRIS = 0;
    TEST_PIN_LAT = 0;

    // Register PWM EOC callback
    PWM_GeneratorEOCEventCallbackRegister(MyPWMInterrupt);

    // Clear and enable PWM1 interrupt
    IFS4bits.PWM1IF = 0;
    IEC4bits.PWM1IE = 1;

    // Enable PWM generators
    PG1CONLbits.ON = 1;
    PG2CONLbits.ON = 1;
    PG3CONLbits.ON = 1;

    // Enable global interrupts
    __builtin_enable_interrupts();
}

//Change Ampltude (Need math calculations)
void vfd_setDutyCycle(float percent){
     // Optional: implement later
}

//Frequency Control Logic
void vfd_SetFrequency(float freq){
    pwm_UpdateFreq(&pwm_A,freq);
    pwm_UpdateFreq(&pwm_B,freq);
    pwm_UpdateFreq(&pwm_C,freq);
}

void vfd_SetDirection(Direction direct){
    pwm_A.direction = direct;
    pwm_B.direction = direct;
    pwm_C.direction = direct;
}

float Freq = 1;
float dutyCycle = 0;

void vfd_Update(float newFreq){
    if (newFreq != Freq && newFreq > 0 && newFreq < 60)
    {
        vfd_SetFrequency(newFreq);
        Freq = newFreq;
    }
}

//Interrupt Logic for updating Duty Cycle
static float index_acc = 0.0f;

void MyPWMInterrupt(void)
{
    uint16_t dutyA = pwm_NextVal(&pwm_A);
    uint16_t dutyB = pwm_NextVal(&pwm_B);
    uint16_t dutyC = pwm_NextVal(&pwm_C);

    // Update PWM registers
    setPWM_Cycle(1, dutyA);
    setPWM_Cycle(2, dutyB);
    setPWM_Cycle(3, dutyC);

    // Increment cycle counter
    index_acc += 0.08f;               // advance by stepSize
    if (index_acc >= table_Size) {
        index_acc -= table_Size;      // wrap around
        TEST_PIN_LAT ^= 1;            // LED toggles once per sine period
    }
}




