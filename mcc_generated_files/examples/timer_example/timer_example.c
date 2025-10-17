/**
 * Timer Toggle LED - Polled Example Driver File.
 * 
 * @file timer_example.c
 * 
 * @addtogroup timer_example
 * 
 * @brief This is the generated example implementation for Timer Toggle LED in Polled mode.
 *
 * @version Timer Example Driver Version 1.0.0
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

/* 1. Timer Toggle LED -> Polled implementation. Copy this code to your project source, e.g., to main.c  */
/* ------------------------------------------------------------------
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/timer/{timer_header}.h" // TODO: Replace {timer_header} with the corresponding header file for your project (ex: tmr1.h)

static void Timer_Callback(void) 
{
    IO_LED_Toggle();
}

int main(void) 
{
    const struct TIMER_INTERFACE *timer = &TimerX; // TODO: Replace with the timer instance in your project

    SYSTEM_Initialize();
    timer->TimeoutCallbackRegister(Timer_Callback);

    while (1) 
    {
        timer->Tasks();
    }
}
------------------------------------------------------------------ */

/**
 End of File
*/