#include "shell.h"

/**
 * hsh - main shell loop
 * @inf: the parameter & return info struct
 * @ev: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *inf, char **ev)
{
	ssize_t r = 0;
	int built_ret = 0;

	while (r != -1 && built_ret != -2)
	{
		clr_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(inf);
		if (r != -1)
		{
			set_info(inf, ev);
			built_ret = find_builtin(inf);
			if (built_ret == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_hist(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->stat)
		exit(inf->stat);
	if (built_ret == -2)
	{
		if (inf->err_len == -1)
			exit(inf->stat);
		exit(inf->err_len);
	}
	return (built_ret);
}

/**
 * find_builtin - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */

int find_builtin(info_t *inf)
{
	int i, built_in_ret = -1;
	builtin_table builtint[] = {
		{"exit", _mexit},
		{"env", _menv},
		{"help", _mhelp},
		{"history", _mhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mcd},
		{"alias", _malias},
		{NULL, NULL}};

	for (i = 0; builtint[i].type; i++)
		if (_strcmp(inf->argv[0], builtint[i].type) == 0)
		{
			inf->line_count++;
			built_in_ret = builtint[i].func(inf);
			break;
		}
	return (built_in_ret);
}

