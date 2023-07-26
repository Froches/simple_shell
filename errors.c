#include "shell.h"

/**
 * eputs - function that prints output string
 * @str: the string to print
 *
 * Return: Nothing
 */
void eputs(char *str)
{
	int b = 0;

	if (!str)
		return;
	while (str[b] != '\0')
	{
		eputchar(str[b]);
		b++;
	}
}

/**
 * eputchar - function that writes character c to stderr
 * @c: character to write
 *
 * Return: 1 on success
 * On error, -1 is returned, and errno is set appropriately.
 */
int eputchar(char c)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(2, buf, b);
		b = 0;
	}
	if (c != BUF_FLUSH)
		buf[b++] = c;
	return (1);
}

/**
 * putfd - writes a  character to the given file descriptor
 * @c: Character to print
 * @fd: file descriptor to write to
 * Return: 1 on success. -1 on error.
 */
int putfd(char c, int fd)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(fd, buf, b);
		b = 0;
	}
	if (c != BUF_FLUSH)
		buf[b++] = c;
	return (1);
}

/**
 * putsfd - prints an input string to file descriptor
 * @str: string to be printed
 * @fd: file descriptor to write to
 *
 * Return: the number of chars put
 */
int putsfd(char *str, int fd)
{
	int b = 0;

	if (!str)
		return (0);
	while (*str)
	{
		b += putfd(*str++, fd);
	}
	return (b);
}
