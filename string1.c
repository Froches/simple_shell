#include "shell.h"
/**
 * _strcpy - function that copies a string to destination
 * @dest: pointer to destination
 * @src: pointer to source string
 * Return: returns pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == 0 || src == 0)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);

}
/**
 * _strdup - function that duplicates strings
 * @str: string to be be duplicated
 * Return: pointer to newly allocated duplicate of input string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - function that prints a string to stdout
 * @str: the string to print
 *
 * Return: nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
/**
 * _putchar - function that returns characters
 * @ch: character to be printed
 * Return: integer
 */
int _putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}
