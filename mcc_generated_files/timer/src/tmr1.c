/**
 * TMR1 Generated Driver Source File 
 * 
 * @file      tmr1.c
 * 
 * @ingroup   timerdriver
 * 
 * @brief     This is the generated driver source file for TMR1 driver
 *
 * @skipline @version   Firmware Driver Version 1.6.1
 *
 * @skipline @version   PLIB Version 1.5.5
 *
 * @skipline  Device : dsPIC33CK1024MP710
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

// Section: Included Files
#include "../tmr1.h"
#include "../timer_interface.h"

// Section: Data Type Definitions

#define MASK_32_BIT_LOW 0x0000FFFFU
#define MASK_32_BIT_HIGH 0xFFFF0000U

// Section: File specific functions

static void (*TMR1_TimeoutHandler)(void) = NULL;

// Section: Driver Interface

const struct TIMER_INTERFACE Clock = {
    .Initialize            = &TMR1_Initialize,
    .Deinitialize          = &TMR1_Deinitialize,
    .Start                 = &TMR1_Start,
    .Stop                  = &TMR1_Stop,
    #if TIMER_PERIODCOUNTSET_API_SUPPORT
    .PeriodCountSet        = &TMR1_PeriodCountSet,
    #endif
    .PeriodSet             = &TMR1_PeriodSet,
    .PeriodGet             = &TMR1_PeriodGet,
    .CounterGet            = &TMR1_CounterGet,
    .InterruptPrioritySet  = &TMR1_InterruptPrioritySet,
    .TimeoutCallbackRegister = &TMR1_TimeoutCallbackRegister,
    .Tasks          = NULL
};

// Section: TMR1 Module APIs

void TMR1_Initialize (void)
{
    //TCS External; TSYNC disabled; TCKPS 1:1; TGATE disabled; TECS FCY; PRWIP Write complete; TMWIP Write complete; TMWDIS disabled; TSIDL disabled; TON disabled; 
    T1CON = 0x102U;
    //TMR 0x0; 
    TMR1 = 0x0U;
    //Period 1 ms; Frequency 4,000,000 Hz; PR 3999; 
    PR1 = 0xF9FU;
    
    TMR1_TimeoutCallbackRegister(&TMR1_TimeoutCallback);

    TMR1_Start();
}

void TMR1_Deinitialize (void)
{
    TMR1_Stop();
    
    T1CON = 0x0U;
    TMR1 = 0x0U;
    PR1 = 0xFFFFU;
}

void TMR1_Start( void )
{
    //Clear interrupt flag
    IFS0bits.T1IF = 0;
    //Enable the interrupt
    IEC0bits.T1IE = 1;
    
    // Start the Timer 
    T1CONbits.TON = 1;
}

void TMR1_Stop( void )
{
    // Stop the Timer 
    T1CONbits.TON = 0;
    
    //Disable the interrupt
    IEC0bits.T1IE = 0;
}

void TMR1_PeriodSet(uint32_t count)
{
    PR1 = (uint16_t)(count & MASK_32_BIT_LOW);
}

void TMR1_InterruptPrioritySet(enum INTERRUPT_PRIORITY priority)
{
    IPC0bits.T1IP = priority;
}

void TMR1_TimeoutCallbackRegister(void (*handler)(void))
{
    if(NULL != handler)
    {
        TMR1_TimeoutHandler = handler;
    }
}

void __attribute__ ((weak)) TMR1_TimeoutCallback( void )
{ 

} 

/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    (*TMR1_TimeoutHandler)();
    IFS0bits.T1IF = 0;
}

#if TIMER_PERIODCOUNTSET_API_SUPPORT
void TMR1_PeriodCountSet(size_t count)
{
    PR1 = count & MASK_32_BIT_LOW;
}
#endif

/**
 End of File
*/
