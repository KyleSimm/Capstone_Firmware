#include <xc.h>
#include "pwm_Lookup.h"
#include <stdint.h>
#include <math.h>

// Example table of frequency ? period values
//Change to 256++ Values
uint16_t sine_table[table_Size];

void init_sine_table(void) {
    for(int i = 0; i < table_Size; i++) {
        sine_table[i] = (uint16_t)((sin(2.0 * M_PI * i / table_Size) + 1.0) * 0.5 * pwm_Max + 0.5);
    }
}


//Duty Size?
uint16_t pwm_NextVal(PWM_State *state) {
    uint16_t i = (uint16_t)state->index;                 // integer part
    float frac = state->index - i;                      // fractional part
    uint16_t next = sine_table[(i + 1) % table_Size];   // next table value
    uint16_t value = (uint16_t)((1.0f - frac) * sine_table[i] + frac * next);

    // Update index
    if (state->direction == FORWARD) {
        state->index += state->step_size;
    } else {
        state->index -= state->step_size;
    }

    // Wrap around
    if (state->index >= table_Size) state->index -= table_Size;
    if (state->index < 0) state->index += table_Size;

    return value;
}



//Frequency
#define PWM_FREQ 16000.0f
void pwm_UpdateFreq(PWM_State *state, float frequency)
{
    // updateRate = how many times per second pwm_nextVal() is called
    state->step_size = frequency * table_Size / PWM_FREQ  ; //Currently 16KHz frequency
}

