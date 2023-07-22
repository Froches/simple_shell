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
	int result = 0;
	int sign = 1;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
