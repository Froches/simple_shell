#include "shell.h"

/**
 * _my_exit -function that exits the shell
 * @info: Struct that contains arguments
 *
 * Return: -2 to indicate exit command should be processed by the shell.
 */
int _my_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* if there is a 2nd argument after the 'exit' cmd*/
	{
		/* Convert the exit status to an int using _erratoi function */
		exitcheck = _erratoi(info->argv[1]);

		if (exitcheck == -1) /*if the conversion resulted in an error*/
		{
			/*Set the shell status to 2 to indicate an error */
			info->status = 2;

			/* Print an error message */
			print_error(info, "Illegal number: ");
			eputs(info->argv[1]);
			eputchar('\n');
			return (1);
		}

		/* Else, store the exit status in info->err_num*/
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;

	/*Indicate that the shell should process the exit command*/
	return (-2);
}

/**
 * _mycd -  function for changing the current working directory
 * @info: Struct containing parameters
 *
 * Return: 0 on success, 1 on error.
 */
int _mycd(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024); /* Get curr working dir and store in 's'*/
	if (!str) /* Check if getcwd failed */
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])/* Check if no arg is provided after the 'cd' cmd */
	{
		dir = _getenv(info, "HOME=");/*Get the valu of 'HOME' env var*/
		/*If 'HOME' is not set, set the current dir to root dir '/'*/
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0) /*Check if the arg is '-'*/
	{
		/*If 'OLDPWD' is not set, print the current working directory*/
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	} else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1) /*if chdir returned an error*/
	{
		print_error(info, "can't cd to "); /*print an error message*/
		eputs(info->argv[1]), eputchar('\n');
	} else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - function to display help information
 * @info: Struct that contanins arguments
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	/*Set 'arg_array' to point to the same array as 'info->argv'*/
	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
