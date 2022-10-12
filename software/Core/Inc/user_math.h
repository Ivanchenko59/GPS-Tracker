/*
 * user_math.h
 *
 *  Created on: 31 авг. 2022 г.
 *      Author: ivanc
 */

#ifndef __MATH_H
#define __MATH_H

#define R1	10000
#define R2	33000

#define GET_INPUT_VOLTAGE(vout, r1, r2) (((vout) * (r1 + r2)) / (r2))

uint16_t get_adc_resolution(ADC_HandleTypeDef *hadc);
uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);


#endif /* __MATH_H */
