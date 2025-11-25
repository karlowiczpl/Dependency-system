#ifndef DEPENDENCY_SYSTEM_H
#define DEPENDENCY_SYSTEM_H

#include <stdint.h>

#define OUT_COUNT 8
#define PWM_COUNT 8
#define IN_COUNT 8
#define TEMP_COUNT 8
#define ROLLER_COUNT 8

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
  uint8_t inputs[IN_COUNT][4];
  uint8_t outputs[OUT_COUNT][2];
  uint8_t temps[TEMP_COUNT][10];
  uint8_t rollers[ROLLER_COUNT][3];
  uint8_t pwms[PWM_COUNT][4];
}FX_INDENTIFICATORS_T;

typedef struct
{
  uint8_t outputs_restore_states[OUT_COUNT];
  uint8_t pwms_restore_states[PWM_COUNT];

  FX_INDENTIFICATORS_T fx_indentificators;
  DEPENDENCY_T dependences[256];
}DEPENDENCY_SYSTEM_DATA_T;

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

/*
 *    HOOKS
 */

void dSet_out_callback(uint8_t id, uint8_t pin);
void dSet_pwm_callback(uint8_t id, uint8_t pin);
void dSet_rol_callback(uint8_t id, uint8_t pin);

/*
*     STATIC FUNCTIONS
*/

static void __connect_fx_with_input(uint8_t fx_num, uint8_t* inputs_array, uint8_t type);

#endif // !DEPENDENCY_SYSTEM_H
