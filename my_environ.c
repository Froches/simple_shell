#include "shell.h"

/**
 * _myenv - function that prints working environment
 * @info: Struct that contains arguments
 *
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - function that gets the value of an env variable
 * @info: Struct that contains arguments
 * @name: environment vairable name
 *
 * Return: the value of the env variable
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = start_with(node->s, name);
		if (p && *p)
			return (0);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - function that creates new env variable or modifies existing one
 * @info: Struct that contains arguments
 *
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - function that removes an environment variable
 * @info: Struct that contains arguments
 *
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int b;

	if (info->argc == 1)
	{
		eputs("Too few arguments.\n");
		return (1);
	}
	for (b = 1; b <= info->argc; b++)
		_unsetenv(info, info->argv[b]);

	return (0);
}

/**
 * populate_env_list - function that populates a linked list
 * @info: Struct that contains arguments
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	info->env = node;

	return (0);
}
