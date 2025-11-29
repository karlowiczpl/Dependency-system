#include <stdint.h>
#include <stdio.h>

#include "dependency_system.h"

DEPENDENCY_SYSTEM_DATA_T* dependency_data;

void setup_dependency_system(uint8_t* data)
{
  dependency_data = (DEPENDENCY_SYSTEM_DATA_T*)data; 

  for(uint8_t i = 0; i < OUT_COUNT; i++)
  {
    dSet_out_callback(0, i, dependency_data->outputs_restore_states[i]);
  }
  for(uint8_t i = 0; i < PWM_COUNT; i++)
  {
    dSet_pwm_callback(0, i, dependency_data->pwms_restore_states[i]);
  }
}

void dSet_fx_mode(uint8_t fx_num, uint8_t mode)
{
  dependency_data->dependences[fx_num].action = mode;
}

void __connect_fx_with_input(uint8_t fx_num, uint8_t* inputs_array, uint8_t type)
{
  uint16_t states = 0;

  for(uint8_t i = 0; i < IN_COUNT; i++)
  {
    states |= inputs_array[i] << i;
    if(inputs_array[i])
    {
      dependency_data->fx_indentificators.inputs[i][type] = fx_num;
    }
  }

  dependency_data->dependences[fx_num].activator_pins = states;
}

void dSet_connect_fx_with_press_short(uint8_t fx_num, uint8_t* inputs_array)
{
  __connect_fx_with_input(fx_num, inputs_array, _PRESS_SHORT);
}

void dSet_connect_fx_with_press_long(uint8_t fx_num, uint8_t* inputs_array)
{
  __connect_fx_with_input(fx_num, inputs_array, _PRESS_LONG);
}

void dSet_connect_fx_with_rising_edge(uint8_t fx_num, uint8_t* inputs_array)
{
  __connect_fx_with_input(fx_num, inputs_array, _RISING_EDGE);
}

void dSet_connect_fx_with_falling_edge(uint8_t fx_num, uint8_t* inputs_array)
{
  __connect_fx_with_input(fx_num, inputs_array, _FALLING_EDGE);
}

void dSet_connect_fx_with_self_output(uint8_t fx_fun, uint8_t* outputs_array)
{
  dependency_data->dependences[fx_fun].driver_id = 0;
  dependency_data->dependences[fx_fun].action = _OUTPUT;

  uint16_t states = 0;
  for(uint8_t i = 0; i < OUT_COUNT; i++)
  {
    states |= outputs_array[i] << i;
  }

  dependency_data->dependences[fx_fun].action_pins = states;
}

void dSet_connect_fx_with_output(uint8_t fx_fun, uint8_t* outputs_array, uint8_t id, uint8_t outputs_count)
{
  dependency_data->dependences[fx_fun].action = _OUTPUT;
  dependency_data->dependences[fx_fun].driver_id = id;

  uint16_t states = 0;
  for(uint8_t i = 0; i < outputs_count; i++)
  {
    states |= outputs_array[i] << i;
  }

  dependency_data->dependences[fx_fun].action_pins = states;
}

void dSet_fx_t1(uint8_t fx, uint8_t time)
{
  dependency_data->dependences[fx].t1 = time;
}

void dSet_fx_t2(uint8_t fx, uint8_t time)
{
  dependency_data->dependences[fx].t2 = time;
}

void dSet_connect_fx_with_self_roller(uint8_t fx_fun, uint8_t* outputs_array)
{
  dependency_data->dependences[fx_fun].action = _ROLLER;
  dependency_data->dependences[fx_fun].driver_id = 0;

  uint16_t states = 0;
  for(uint8_t i = 0; i < OUT_COUNT; i++)
  {
    states |= outputs_array[i] << i;
  }

  dependency_data->dependences[fx_fun].action_pins = states;
}

void dSet_connect_fx_with_roller(uint8_t fx_fun, uint8_t* outputs_array, uint8_t id, uint8_t outputs_count)
{
  dependency_data->dependences[fx_fun].action = _ROLLER;
  dependency_data->dependences[fx_fun].driver_id = id;

  uint16_t states = 0;
  for(uint8_t i = 0; i < outputs_count; i++)
  {
    states |= outputs_array[i] << i;
  }

  dependency_data->dependences[fx_fun].action_pins = states;
}

void dSet_time_counter_mode(uint8_t fx_fun, uint8_t mode)
{
  dependency_data->dependences[fx_fun].time_mode = mode;
}

void dSet_output_states_after_boot(uint8_t* outputs_array)
{
  #if OUT_COUNT > 0
    for(uint8_t i = 0; i < IN_COUNT; i++)
    {
      dependency_data->outputs_restore_states[i] = outputs_array[i];
    }
  #endif /* if OUT_COUNT > 0 */
}

void dSet_pwm_states_after_boot(uint8_t* pwms)
{
  #if PWM_COUNT > 0
    for(uint8_t i = 0; i < PWM_COUNT; i++)
    {
      dependency_data->pwms_restore_states[i] = pwms[i];
    }
  #endif /* if PWM_COUNT > 0 */
}

void __trigger(uint8_t input, uint8_t flag)
{
  uint8_t fx_fun = dependency_data->fx_indentificators.inputs[input][flag];

  if(fx_fun)
  {
    uint8_t id = dependency_data->dependences[fx_fun].driver_id;
    uint8_t activator_pins = dependency_data->dependences[fx_fun].activator_pins;
    uint8_t action_pins = dependency_data->dependences[fx_fun].action_pins;
    uint8_t action = dependency_data->dependences[fx_fun].action;

    if(activator_pins & (1 << input))
    {
      for(uint8_t j = 0; j < 16; j++)
      {
        if(action_pins & (1 << j))
        {
          dSet_out_callback(id, j, action);
        }
      }
    }
  }
}
void trigger_press_short(uint8_t input)
{
  __trigger(input, _PRESS_SHORT);
}

void trigger_press_long(uint8_t input)
{
  __trigger(input, _PRESS_LONG);
}

void trigger_rising_edge(uint8_t input)
{
  __trigger(input, _RISING_EDGE);
}

void trigger_fallig_edge(uint8_t input)
{
  __trigger(input, _FALLING_EDGE);
}
