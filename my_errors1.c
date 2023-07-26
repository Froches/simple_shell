#include "shell.h"

/**
 * _erratoi - function that converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if there are not numbers in string and -1 on error
 */
int _erratoi(char *s)
{
	int b = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (b = 0;  s[b] != '\0'; b++)
	{
		if (s[b] >= '0' && s[b] <= '9')
		{
			res *= 10;
			res += (s[b] - '0');
			if (res > INT_MAX)
				return (-1);
		} else
			return (-1);
	}
	return (res);
}

/**
 * print_error - function that prints error messages
 * @info: Struct containing parameters
 * @estr: the string containing a specific error type
 *
 * Return: 0 if there are no numbers in string, and -1 on error
 */
void print_error(info_t *info, char *estr)
{
	eputs(info->fname);
	eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	eputs(": ");
	eputs(info->argv[0]);
	eputs(": ");
	eputs(estr);
}

/**
 * print_d - prints decimals (integers) in base 10.
 * @input: the input
 * @fd: file descriptor to write in
 *
 * Return: no. of chars printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int b, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (b = 1000000000; b > 1; b /= 10)
	{
		if (_abs_ / b)
		{
			__putchar('0' + current / b);
			count++;
		} current %= b;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - function that converts digits
 * @num: number to convert
 * @base: the base to convert into
 * @flags: argument flags
 *
 * Return: pointer to string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function that replaces comments with NULL
 * @buf: pointer to the string to work on
 *
 * Return: 0 always.
 */
void remove_comments(char *buf)
{
	int b;

	for (b = 0; buf[b] != '\0'; b++)
		if (buf[b] == '#' && (!b || buf[b - 1] == ' '))
		{
			buf[b] = '\0';
			break;
		}
}
