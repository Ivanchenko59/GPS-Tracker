/*
 * user.c
 *
 *  Created on: Aug 11, 2022
 *      Author: ivanc
 */

#include "user.h"

const char* valid_numbers[NUM_OF_NUMBERS] =
	{
			"+380951879242",
			"+380666874820"
	};


uint8_t gsm_number_validation(const char* number)
{
	uint8_t res = 0;
	if (NUM_OF_NUMBERS > 0) {
		for (int num = 0; num < NUM_OF_NUMBERS; num++) {
			res = strcmp(number, valid_numbers[num]);
			if (res == 0) return 1;
		}
	}
	return 0;
}
