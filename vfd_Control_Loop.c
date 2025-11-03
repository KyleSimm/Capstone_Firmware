#include <xc.h>
#include "vfd_Control_Loop.h"
#include <stdint.h>


// {index, stepSize, direction}
static PWM_State my_pwm_A = {0,.08,1};                      // 0   phase shift
static PWM_State my_pwm_B = {table_Size / 3, .08, 1};       // 120 phase shift
static PWM_State my_pwm_C = {2 * table_Size / 3, .08, 1};   // 240 Phase shift

void vfd_Init(void)
{
    init_sine_table();
    
    //PWM Set to 5 Hz
    float initialFreq = 50.0f;
    vfd_SetFrequency(initialFreq); //Also Sets StepSize
    setPWM_Cycle(1, 1);
    
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
    pwm_UpdateFreq(&my_pwm_A,freq);
    pwm_UpdateFreq(&my_pwm_B,freq);
    pwm_UpdateFreq(&my_pwm_C,freq);
}

void vfd_SetDirection(Direction direct){
    my_pwm_A.direction = direct;
    my_pwm_B.direction = direct;
    my_pwm_C.direction = direct;
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

void MyPWMInterrupt(enum PWM_GENERATOR genNum)
{
    
    uint16_t dutyA = pwm_NextVal(&my_pwm_A);
    uint16_t dutyB = pwm_NextVal(&my_pwm_B);
    uint16_t dutyC = pwm_NextVal(&my_pwm_C);

    // Update PWM registers
    setPWM_Cycle(1, dutyA);
    setPWM_Cycle(2, dutyB);
    setPWM_Cycle(3, dutyC);

    // Increment cycle counter
    
        TEST_PIN_LAT ^= 1;            // LED toggles once per sine period
        
        
        IFS4bits.PWM1IF = 0; 
}




