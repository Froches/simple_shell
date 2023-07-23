#include "shell.h"

/**
 * freeP - frees a pointer and sets the address to NULL
 * @ptr: address of the pointer to free
 *
 * Return: 1 if successful, else returns 0.
 */
int freeP(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
