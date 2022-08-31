/*
 * validation.h
 *
 *  Created on: Aug 11, 2022
 *      Author: ivanc
 */

#ifndef GSM_V5_INC_VALIDATION_H_
#define GSM_V5_INC_VALIDATION_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
	char number[16];
	char msg[254];
}msg_data_t;

uint8_t gsm_number_validation(const char* number);

#endif /* GSM_V5_INC_VALIDATION_H_ */
