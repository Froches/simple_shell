#include "shell.h"

/**
 * _myhistory - function to display the history of commands
 * @info: Struct containing parameters
 *
 *  Return: Always returns 0
 */
int _myhistory(info_t *info)
{
	/*Call the 'print_list' function to print the history of commands*/
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - function to unset an alias by name
 * @info: Struct containing parameters
 * @s: Pointer to the string representing the alias to unset
 *
 * Return: 1 if the alias is not found or incorrectly formatted, 0 on success.
 */
int unset_alias(info_t *info, char *s)
{
	char *p, c;
	int ret;

	/*Find the position of the equal sign (=) in the provided 'str'*/
	p = _strchr(s, '=');
	/* If no (=) is found, return 1 to indicate an error*/
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	/*remove the node at the found index from the 'alias' linked list*/
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, s, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - function to set or update an alias
 * @info: Struct containing parameter
 * @s: Pointer to the string representing the alias to set/update
 * Return: 1 if the alias is not correctly formatted, 0 on success.
 */
int set_alias(info_t *info, char *s)
{
	char *p;

	p = _strchr(s, '=');
	/*If no equal sign is found, return 1 to indicate an error*/
	if (!p)
		return (1);
	/*Increment 'p' to move to the character after the equal sign (=)*/
	/*If the char after the equal sign is NULL, no value for the alias.*/
	/*Unset alias and return the result of 'unset_alias' function.*/
	if (!*++p)
		return (unset_alias(info, s));

	unset_alias(info, s);
	return (add_node_end(&(info->alias), s, 0) == NULL);
}

/**
 * print_alias - function to print an alias in a formatted manner
 * @node: Pointer to the list node containing the alias
 *
 * Return: 0 on success, 1 if the node is NULL.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *e = NULL;

	/*Check if the provided 'node' is not NULL*/
	if (node)
	{
		/*Find position of equal sign in the alias string of 'node'*/
		p = _strchr(node->s, '=');
		/*Iterate through alias str from the start to position of (=)*/
		for (e = node->s; e <= p; e++)
		_putchar(*e); /*Print each character of the alias name*/
		_putchar('\''); /*Print a single quote to separate alias name from value*/
		_puts(p + 1); /*Print the alias value*/
		_puts("'\n"); /*Print (') and new line char to format output*/
		return (0);
	}
	return (1);
}

/**
 * _myalias - function to handle alias operations
 * @info: Struct containing parameters
 *
 *  Return: Always returns 0.
 */
int _myalias(info_t *info)
{
	int b = 0;
	char *p = NULL;
	list_t *node = NULL;

	/*Check if there is only one argument after the 'alias' command*/
	if (info->argc == 1)
	{
		/*If yes, print all aliases in a formatted manner*/
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	/*Loop through each argument after the 'alias' command*/
	for (b = 1; info->argv[b]; b++)
	{
		p = _strchr(info->argv[b], '='); /*Find the position of (=)*/
		/*If the (=) is found, it means it's an alias definition*/
		if (p)
			set_alias(info, info->argv[b]); /*Set or update alias*/
		else
		/*Call print_alias to print it out in a formatted manner*/
			print_alias(node_starts_with(info->alias, info->argv[b], '='));
	}

	return (0);
}
