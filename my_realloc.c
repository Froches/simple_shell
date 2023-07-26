#include "shell.h"

/**
 * _memset - fills memory with bytes
 * @str: the pointer to the memory address
 * @b: the byte that fills *str
 * @n: the amount of bytes filled in str
 * Return: (str) a pointer to the memory area str
 */
char *_memset(char *str, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		str[i] = b;
	}

	return (str);
}

/**
 * ffree - frees a string of strings
 * @bb: string of strings
 */
void ffree(char **bb)
{
	char **c = bb;

	if (!bb)
		return;
	while (*bb)
		free(*bb++);
	free(c);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous allocated block
 * @prev_size: byte size of previous block
 * @curr_size: byte size of current block
 *
 * Return: pointer to previous block.
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int curr_size)
{
	char *p;

	if (!ptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(ptr), NULL);
	if (curr_size == prev_size)
		return (ptr);

	p = malloc(curr_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < curr_size ? curr_size : curr_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}
