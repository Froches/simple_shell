#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int b, j;
	char *str = dest;

	b = 0;
	while (src[b] != '\0' && b < n - 1)
	{
		dest[b] = src[b];
		b++;
	}
	if (b < n)
	{
		j = b;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int b, j;

	char *c = dest;

	b = 0;
	j = 0;
	while (dest[b] != '\0')
		b++;
	while (src[j] != '\0' && j < n)
	{
		dest[b] = src[j];
		b++;
		j++;
	}
	if (j < n)
		dest[b] = '\0';
	return (c);
}

/**
 **_strchr - locates a character in a string
 *@str: the string to be parsed
 *@ch: the character to look for
 *Return: (str) a pointer to the memory area
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
