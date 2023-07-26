#include "shell.h"

/**
 * get_environ - function to get the env variables as an array of strings
 * @info: Struct that contains parameters
 *
 * Return: Pointer to an array of strings containing environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Custom function to unset an environment variable
 * @info: Pointer to struct that contains parameters
 * @var: Pointer to the string representing the environment variable to unset
 *
 * Return: 1 if the environment variable is successfully unset, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t b = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		/*Find if the node's string starts with the 'var' string*/
		p = start_with(node->s, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), b);
			b = 0;
			node = info->env;
			continue;
		}
		/*Move to the next node in the linked list.*/
		node = node->next;
		b++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Custom function to set an environment variable
 * @info: Struct containing parameters
 * @var: Pointer to the string representing the environment variable name
 * @value: Pointer to string representing the value to assign to the env var.
 *
 * Return: 0 on success, 1 on failure.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	/*Check if either the 'var' or 'value' string pointer is NULL*/
	if (!var || !value)
		return (0);

	/*Allocate memory for a buff to hold the env var and its value*/
	buf = malloc(strlen(var) + strlen(value) + 2);
	if (!buf)
		return (1);
	/*Construct the env var string in 'buf' in the format 'var=value'*/
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	/*Loop through each node in the 'info->env' linked list*/
	while (node)
	{
		p = start_with(node->s, var);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
