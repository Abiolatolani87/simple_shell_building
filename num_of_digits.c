#include "main.h"

/**
 * num_of_digits - count digits in n
 * @num: number to count
 * Return: number of dogits
 */

int num_of_digits(unsigned int num)
{
	unsigned int n = num;
	int digits = 1;

	while (n >= 10)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}
