/**
 * PWM Duty Cycle Update with Analog Input Source - Polled Example Driver File.
 * 
 * @file pwm_example.c
 * 
 * @addtogroup pwm_example
 * 
 * @brief This is the generated example implementation for PWM Duty Cycle Update with Analog Input Source in Polled mode.
 *
 * @version PWM Example Driver Version 1.0.0
*/
/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

/* 3. PWM Duty Cycle Update with Analog Input Source -> Polled implementation. Copy this code to your project source, e.g., to main.c  */

/* ------------------------------------------------------------------
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/pwm/{sccp_header}.h" // TODO: Replace {sccp_header} with the corresponding SCCP header file for your project (ex: sccp1.h)
#include "mcc_generated_files/adc/{adc_header}.h" // TODO: Replace {adc_header} with the corresponding ADC header file for your project (ex: adc1.h)
#include "mcc_generated_files/timer/{timer_header}.h" // TODO: Replace {timer_header} with the corresponding timer header file for your project (ex: tmr1.h)

#define MAXIMUM_INPUT_VALUE XXXX // TODO: Replace with the desired maximum read in value from the ADC (a potentiometer example could be 4100)
#define ACTIVE_HIGH // TODO: Comment out this line for Active Low configurations

static const struct PWM_INTERFACE *pwm = &PWMx; // TODO: Replace with the PWM instance in your project

static void UpdateDutyCycle(uint16_t dutyCycle)
{
    pwm->DutyCycleSet(dutyCycle);
}

static void Timer_Callback(void)
{
    const struct ADC_INTERFACE *adc = &ADCx; // TODO: Replace with the ADC instance in your project
    uint16_t adcResult = adc->ConversionResultGet(Channel_ANx); // TODO: Replace with the ADC Channel you selected in the Pin Grid View

    // The adcResult is divided by the maximum expected ADC value to create a percentage. It is then multiplied by the PWM period register low (CCPxPRL) to calculate an updated duty cycle.
    #ifdef ACTIVE_HIGH
    uint16_t dutyCycle = ((double) adcResult / (double) MAXIMUM_INPUT_VALUE) * CCPxPRL; // TODO: Replace the X with the SCCP instance in your project
    #else
    uint16_t dutyCycle = (1.0f - ((double) adcResult / (double) MAXIMUM_INPUT_VALUE)) * CCPxPRL; // TODO: Replace the X with the SCCP instance in your project
    #endif

    UpdateDutyCycle(dutyCycle);
    adc->SoftwareTriggerEnable(); // Trigger the ADC conversion via software
}

int main(void)
{
    const struct TIMER_INTERFACE *timer = &TimerX; // TODO: Replace with the timer instance in your project

    SYSTEM_Initialize();
    
    timer->TimeoutCallbackRegister(Timer_Callback);
    
    while(1)
    {
        pwm->Tasks();
        timer->Tasks();
    }
}
------------------------------------------------------------------ */

/**
 End of File
*/