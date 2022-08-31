/*
 * user_math.c
 *
 *  Created on: 31 авг. 2022 г.
 *      Author: ivanc
 */

#include "stm32f4xx_hal.h"


uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

