#ifndef DEPENDENCY_SYSTEM_H
#define DEPENDENCY_SYSTEM_H

#include <stdint.h>

#define OUT_COUNT 1
#define PWM_COUNT 6
#define IN_COUNT 8
#define TEMP_COUNT 0
#define ROLLER_COUNT 0

#define _FALLING_EDGE 0
#define _RISING_EDGE 1
#define _PRESS_SHORT 2
#define _PRESS_LONG 3

#define _TURN_ON 1
#define _TURN_OFF 2
#define _TOGGLE 3
#define _TURN_ON_FOR_TIME 4
#define _TURN_ON_OFF_FOR_TIME 5
#define _GENERATOR_ 6

#define _OUTPUT 1
#define _ROLLER 2
#define _PWM 3

typedef struct
{
  uint8_t action;
  uint8_t driver_id;
  uint16_t activator_pins;
  uint16_t action_pins;
  uint8_t t1;
  uint8_t t2;
  uint8_t time_mode;
}DEPENDENCY_T;

typedef struct
{
  #if IN_COUNT > 0
    uint8_t inputs[IN_COUNT][4];
  #endif // IN_COUNT > 0
  #if OUT_COUNT > 0
    uint8_t outputs[OUT_COUNT][2];
  #endif // OUT_COUNT > 0
  #if TEMP_COUNT > 0
    uint8_t temps[TEMP_COUNT][10];
  #endif // TEMP_COUNT > 0
  #if ROLLER_COUNT > 0
    uint8_t rollers[ROLLER_COUNT][3];
  #endif // ROLLER_COUNT > 0
  #if PWM_COUNT > 0
    uint8_t pwms[PWM_COUNT][4];
  #endif // PWM_COUNT > 0
}FX_INDENTIFICATORS_T;

typedef struct
{
  #if OUT_COUNT > 0
    uint8_t outputs_restore_states[OUT_COUNT];
  #endif // OUT_COUNT > 0
  #if IN_COUNT > 0
    uint8_t pwms_restore_states[PWM_COUNT];
  #endif // IN_COUNT > 0

  FX_INDENTIFICATORS_T fx_indentificators;
  DEPENDENCY_T dependences[256];
}DEPENDENCY_SYSTEM_DATA_T;

extern DEPENDENCY_SYSTEM_DATA_T* dependency_data;

/*
 *    RUNTIME FUNCTIONS
 */

void setup_dependency_system(uint8_t* data);

void trigger_press_short(uint8_t input);
void trigger_press_long(uint8_t input);
void trigger_rising_edge(uint8_t input);
void trigger_fallig_edge(uint8_t input);

/*
 *    CONFIGURATION FUNCTIONS
 */

void dSet_fx_mode(uint8_t fx_num, uint8_t mode);
void dSet_connect_fx_with_press_short(uint8_t fx_num, uint8_t* inputs_array);
void dSet_connect_fx_with_press_long(uint8_t fx_num, uint8_t* inputs_array);
void dSet_connect_fx_with_rising_edge(uint8_t fx_num, uint8_t* inputs_array);
void dSet_connect_fx_with_falling_edge(uint8_t fx_num, uint8_t* inputs_array);

void dSet_connect_fx_with_self_output(uint8_t fx_fun, uint8_t* outputs_array);
void dSet_connect_fx_with_output(uint8_t fx_fun, uint8_t* outputs_array, uint8_t id, uint8_t outputs_count);

void dSet_connect_fx_with_self_roller(uint8_t fx_fun, uint8_t* outputs_array);
void dSet_connect_fx_with_roller(uint8_t fx_fun, uint8_t* outputs_array, uint8_t id, uint8_t outputs_count);

void dSet_fx_t1(uint8_t fx, uint8_t time);
void dSet_fx_t2(uint8_t fx, uint8_t time);

void dSet_time_counter_mode(uint8_t fx_fun, uint8_t mode);

void dSet_output_states_after_boot(uint8_t* outputs_array);
void dSet_pwm_states_after_boot(uint8_t* pwms);

/*
 *    HOOKS
 */

void dSet_out_callback(uint8_t id, uint8_t pin, uint8_t state);
void dSet_pwm_callback(uint8_t id, uint8_t pin, uint8_t state);
void dSet_rol_callback(uint8_t id, uint8_t pin, uint8_t state);

/*
*     STATIC FUNCTIONS
*/

void __connect_fx_with_input(uint8_t fx_num, uint8_t* inputs_array, uint8_t type);
void __trigger(uint8_t input, uint8_t flag);

#endif // !DEPENDENCY_SYSTEM_H
