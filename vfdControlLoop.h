/* 
 * File:   vfd_control_loop.h
 * Author: School Coding
 *
 * Created on October 16, 2025, 8:41 PM
 */

#ifndef VFD_CONTROL_LOOP_H
#define	VFD_CONTROL_LOOP_H

#ifdef	__cplusplus
extern "C" {
#endif
    #include "pwmLookup.h"

    void vfd_Init(void);
    
    void vfd_SetFrequency(float freq);
    
    void vfd_SetDirection(Direction direct);
    
    void vfd_Update();


#ifdef	__cplusplus
}
#endif

#endif	/* VFD_CONTROL_LOOP_H */

