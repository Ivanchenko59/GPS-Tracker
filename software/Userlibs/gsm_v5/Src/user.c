/*
 * user.c
 *
 *  Created on: Aug 11, 2022
 *      Author: ivanc
 */

#include "user.h"


#define MAX_NUMBERS 	10


 char* valid_numbers[MAX_NUMBERS] =
	{
			"+380951879242",
			"+380666874820",
			"Vodafone"
	};

uint8_t num_of_numbers = 3;

uint8_t gsm_number_validation(const char* number)
{
	int8_t res = 0;
	if (num_of_numbers > 0) {
		for (int num = 0; num < num_of_numbers; num++) {
			res = strcmp(number, valid_numbers[num]);
			if (res == 0) return 1;
		}
	}
	return 0;
}
