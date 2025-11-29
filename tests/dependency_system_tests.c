#include <stdint.h>
#include <stdio.h>

#include "dependency_system.h"

uint8_t data[4000] = {0};

int main()
{ 
  uint8_t inputs_array[8] = {0, 0, 1, 0, 0, 0, 0, 0};
  setup_dependency_system(data);

  dSet_fx_mode(1, 2);

  dSet_connect_fx_with_press_short(2, inputs_array);
  // dSet_connect_fx_with_self_output(1, inputs_array);
  dSet_connect_fx_with_output(2, inputs_array, 3, 8);

  printf("RESTORED DEFAULT STATES\n\n");

  trigger_press_short(0);
  trigger_press_short(1);
  trigger_press_short(2);

  return 0;
}
