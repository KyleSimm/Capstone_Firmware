#include <xc.h>
#include "pwmLookup.h"
#include <stdint.h>
#include <math.h>
// Example table of frequency ? period values

const uint16_t sine_Table[table_Size] = 
{
    1000, 1195, 1383, 1560, 1720, 1859, 1972, 2055,
    2105, 2119, 2097, 2038, 1943, 1816, 1660, 1480,
    1283, 1076,  867,  663,  471,  297,  146,   24,
       0,   10,  111,  299,  562,  887, 1259, 1657
    
};


int16_t pwm_nextVal(PWM_State *state){
    if (state->direction == FORWARD)
        state->index = (state->index + state->step_size);
    else
        state->index = (state->index - state->step_size + table_Size);

    state->index %= table_Size;
    return sine_Table[state->index];
}

void pwm_UpdateStep(PWM_State *state, float frequency)
{
    // updateRate = how many times per second pwm_nextVal() is called
    state->step_size = (frequency / 65.0f) * table_Size;
}

