#include "main.h"

/**
 * itostr - converts integer to string
 * @n: integer to convert
 * Return: pointer to converted string
 *
 * Description - free allocated memory after use
 */
char *itostr(int n)
{
	int digits, digit, divisor, num, i = 0, j = 0;
	char *str = NULL;

	digits = num_of_digits(n);
	str = malloc(sizeof(char) * (digits + 1));
	num = n;

	if (!str)
		return (NULL);

	for (i = digits; i > 0; i--, j++)
	{
		divisor = _pow(10, i - 1);
		digit = num / divisor;

		str[j] = (digit + '0');
		num %= divisor;
	}
	str[j] = '\0';

	return (str);
}

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

/**
 * _pow - calculate power of base, exponent
 * @base: base of power
 * @exp: exponent of power
 * Return: power of base and exp
 */
int _pow(int base, int exp)
{
	int res = 1;
	int i;

	for (i = 0; i < exp; i++)
		res *= base;

	return (res);
}
