#include "shell.h"

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */

void fork_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->stat));
		if (WIFEXITED(inf->stat))
		{
			inf->stat = WEXITSTATUS(inf->stat);
			if (inf->stat == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}

/**
 * find_cmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */

void find_cmd(info_t *inf)
{
	char *path = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
	{
		if (!is_delim(inf->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;
	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=") || inf->argv[0][0] == '/')
				&& is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->stat = 127;
			print_error(inf, "not found\n");
		}
	}
}
