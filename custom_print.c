#include <stdarg.h>
#include "main.h"

/**
 * update - update flag and increment args
 * @n: pointer variable
 * @f: pointer to variable
 */
void update(int *n, int *f)
{
	*n += 1;
	*f = 1;
}

/**
 * print_all - prins anything
 * @format: pointer to separator
 * @...: arguments
 */
void print_all(int fd, const char *const format, ...)
{
	int i = 0, count = 0, num_arg = 0, flag = 0;
	va_list p;
	char *s;

	va_start(p, format);
	i = 0;
	while (format && *(format + i) != '\0')
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
			case 'c':
				_putchar(va_arg(p, int));
				i += 2;
				break;
			case 'i':
				newputs(itostr(va_arg(p, int)));
				i += 2;
				break;
			case 's':
				newputs(va_arg(p, char *));
				i += 2;
				break;
			default:
				break;
			}
		}
		else
			_putchar(format[i]);
		i++;
	}
	va_end(p);
}
