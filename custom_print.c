#include "main.h"

/**
 * custom_print - prints anything
 * @fd: file descriptor
 * @format: pointer to separator
 * @...: arguments
 */
void custom_print(int fd, const char *const format, ...)
{
	int i = 0, va = 0;
	va_list p;
	char *s;

	va_start(p, format);

	while (format && *(format + i) != '\0')
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
			case 'c':
				va = va_arg(p, int);
				write(fd, &va, 1);
				i += 2;
				break;
			case 'd':
				s = itostr(va_arg(p, int));
				write(fd, s, _strlen(s));
				i += 2;
				free(s);
				break;
			case 's':
				s = va_arg(p, char *);
				write(fd, s, _strlen(s));
				i += 2;
				break;
			default:
				break;
			}
		}
		else
		{
			write(fd, &format[i], 1);
			i++;
		}
	}
	va_end(p);
}
