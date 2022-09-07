/*
 * user_math.c
 *
 *  Created on: 31 авг. 2022 г.
 *      Author: ivanc
 */

#include "stm32f4xx_hal.h"

uint16_t get_adc_resolution(ADC_HandleTypeDef *hadc)
{
	uint32_t adc_resolution = hadc->Init.Resolution;
	uint16_t max_adc_val;

	if (adc_resolution == ADC_RESOLUTION_12B) {
		max_adc_val = (1 << 12) - 1;
	}
	else if (adc_resolution == ADC_RESOLUTION_10B) {
		max_adc_val = (1 << 10) - 1;
	}
	else if (adc_resolution == ADC_RESOLUTION_8B) {
		max_adc_val = (1 << 8) - 1;
	}
	else if (adc_resolution == ADC_RESOLUTION_6B) {
		max_adc_val = (1 << 6) - 1;
	}
	return max_adc_val;
}

uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

