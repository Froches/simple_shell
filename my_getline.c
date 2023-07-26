#include "shell.h"

/**
 * input_buf - funtion that buffers chained commands
 * @info: Struct containing parameters
 * @buff: Address of buffer
 * @len: The address of the len variable
 *
 * Return: the total bytes read
 */
ssize_t input_buf(info_t *info, char **buff, size_t *len)
{
	ssize_t b_r = 0;
	size_t len_p = 0;

	if (!*len) /* if there's nothing left in buffer, fill it */
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		b_r = getline(buff, &len_p, stdin);
#else
		b_r = _getline(info, buff, &len_p);
#endif
		if (b_r > 0)
		{
			if ((*buff)[b_r - 1] == '\n')
			{
				(*buff)[b_r - 1] = '\0';
				b_r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*len = b_r;
				info->cmd_buf = buff;
			}
		}
	}
	return (b_r);
}

/**
 * _get_input - function that gets a line minus the newline
 * @info: Struct containing parameters
 *
 * Return: number of bytes read
 */
ssize_t _get_input(info_t *info)
{
	static char *buff; /* the ';' cmd chain buff */
	static size_t b, j, len;
	ssize_t b_r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	b_r = input_buf(info, &buff, &len);
	if (b_r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = b;
		p = buff + b;

		check_chain(info, buff, &j, b, len);
		while (j < len)
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}

		b = j + 1;
		if (b >= len)
		{
			b = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buff;
	return (b_r);
}

/**
 * read_buf - function that reads a buffer
 * @info: Struct containing parameters
 * @buf: buffer to read
 * @i: size
 *
 * Return: bytes read
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t b_r = 0;

	if (*i)
		return (0);
	b_r = read(info->readfd, buf, READ_BUF_SIZE);
	if (b_r >= 0)
		*i = b_r;
	return (b_r);
}

/**
 * _getline - function that gets the first line of input from STDIN
 * @info: Struct containing parameters
 * @ptr: the address of pointer to buffer whether allocated or NULL
 * @length: the size of ptr buffer if it's not NULL
 *
 * Return: length
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t b, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (b == len)
		b = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + b, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + b, k - b);
	else
		_strncpy(new_p, buf + b, k - b + 1);

	s += k - b;
	b = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - function that blocks Ctrl+C from interrupting input
 * @sig_num: the signal number
 *
 * Return: nothing
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
