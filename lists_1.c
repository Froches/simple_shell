#include "shell.h"

/**
 * list_len - function that checks the length of linked list
 * @h: pointer to first node of the linked list
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
		h = h->next;
		b++;
	}
	return (b);
}

/**
 * list_to_strings - function that returns an array of strings
 * @head: pointer to first node of linked list
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t b = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !b)
		return (NULL);
	strs = malloc(sizeof(char *) * (b + 1));
	if (!strs)
		return (NULL);
	for (b = 0; node; node = node->next, b++)
	{
		str = malloc(_strlen(node->s) + 1);
		if (!str)
		{
			for (j = 0; j < b; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->s);
		strs[b] = str;
	}
	strs[b] = NULL;
	return (strs);
}

/**
 * print_list - function that prints all elements of a list
 * @h: pointer to first node of linked list
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
		_puts(convert_number(h->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		b++;
	}
	return (b);
}

/**
 * node_starts_with - function that returns a node that begins with substring
 * @node: a pointer to the head of linked list
 * @substring: the string to pair
 * @c: character after substring to pair
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *substring, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start_with(node->s, substring);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
