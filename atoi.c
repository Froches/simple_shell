#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: returns 1 if in interactive mode, else returns 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delimiters: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delimiters)
{
	while (*delimiters != '\0')
	{
		if (c == *delimiters)
			return (1);
		delimiters++;
	}
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - function tha converts strings to integer
 * @str: string to convert
 * Return: returns zero if there's no strings to convert
 */
int _atoi(char *str)
{
	int sign = 1;
	int flag = 0;
	int output, i;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
