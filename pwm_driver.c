/*
 Set Physical Pins to what is Needed
 */

#include <xc.h>
#include "pwm_driver.h"
//Sets Duty Cycle for PWM Channel

void setPWM_channel(char Phase, uint16_t val){
    
    switch(Phase){
        
        case 'A':
            PG1DC = val; //Sets Channel 1 Duty Cycle
            break;
        
        case 'B':
            PG2DC = val;
            break;
            
        case 'C':
            PG3DC = val;
            break;
            
        default:
            //Maybe Report Error
            break;        
    }
    
}
