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
        {
            _puts("$ ");
        }
        _eputchar(BUF_FLUSH);
        r = get_input(inf);
        if (r != -1)
        {
            set_info(inf, ev);
            built_ret = find_builtin(inf);
            if (built_ret == -1)
            {
                find_cmd(inf);
            }
        }
        else if (interactive(inf))
        {
            _putchar('\n');
        }
        free_info(inf, 0);
    }
    write_hist(inf);
    free_info(inf, 1);
    if (!interactive(inf) && inf->stat)
    {
        exit(inf->stat);
    }
    if (built_ret == -2)
    {
        if (inf->err_len == -1)
        {
            exit(inf->stat);
        }
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
        {
            k++;
        }
    }
    if (!k)
    {
        return;
    }
    path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
    if (path)
    {
        inf->path = path;
        fork_cmd(inf);
    }
    else
    {
        if ((interactive(inf) || _getenv(inf, "PATH=") || inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
        {
            fork_cmd(info);
        }
        else if (*(info->arg) != '\n')
        {
            inf->stat = 127;
            print_error(inf, "not found\n");
        }
    }
}

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
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
        {
            free_info(inf, 1);
            if (errno == EACCES)
            {
                exit(126);
            }
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
            {
                print_error(inf, "Permission denied\n");
            }
        }
    }
}