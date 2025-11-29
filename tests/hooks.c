#include <stdint.h>
#include <stdio.h>

void dSet_out_callback(uint8_t id, uint8_t pin, uint8_t state)
{
  printf("set out %d%d as %d\n", id, pin, state);
}

void dSet_pwm_callback(uint8_t id, uint8_t pin, uint8_t state)
{
  printf("set pwm %d%d as %d\n", id, pin, state);
}

void dSet_rol_callback(uint8_t id, uint8_t pin, uint8_t state)
{
  printf("set rol %d%d as %d\n", id, pin, state);
}
