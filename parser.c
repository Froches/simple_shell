#include "shell.h"

/**
 * is_cmd - function that checks if a file is executable or not
 * @info: member of the info struct
 * @path: path in which to check for file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function that duplicates characters
 * @pathstr: Pointer to PATH string
 * @start: index to start from
 * @stop: index to stop at
 *
 * Return: pointer to a new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int b = 0, k = 0;

	for (k = 0, b = start; b < stop; b++)
		if (pathstr[b] != ':')
			buf[k++] = pathstr[b];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds a command in the PATH string
 * @info: member of the info struct
 * @pathstr: the PATH string
 * @cmd: command to find in path
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int b = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[b] || pathstr[b] == ':')
		{
			path = dup_chars(pathstr, curr_pos, b);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[b])
				break;
			curr_pos = b;
		}
		b++;
	}
	return (NULL);
}
