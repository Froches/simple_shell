#include "shell.h"

/**
 * _strcmp - compares two string inputs
 * @s1: first string input
 * @s2: second string input
 * Return: negative if s1 < s2, positive if s1 > s2, zero s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * strlen - returns the length of the string inputted
 * @str: string input
 * Return: integer
 */
size_t strlen(const char *str)
{
	size_t len = 0;

	while (*str++)
		len++;
	return (len);
}

/**
 * start_with - checks if str starts with prf
 * @str: string to be checked
 * @prf: prefix to be search for
 * Return: returns the address of next str or NULL
 */
char *start_with(const char *str, const char *prf)
{
	while (*prf)
		if (*prf++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _strcat - concatenates two strings
 * @src: source buffer
 * @dest: destination buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
