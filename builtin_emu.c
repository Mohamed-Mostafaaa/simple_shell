#include "shell.h"

/**
 * _mexit - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *       constant function prototype.
 * Return: exits with a given exit status
 *          (0) if info.argv[0] != "exit"
 */

int _mexit(info_t *inf)
{
    int exitcheck;

    if (inf->argv[i]) /* If there is an exit arguement */
    {
        exitcheck = _erratoi(inf->argv[1]);
        if (exitcheck == -1)
        {
            inf->stat = 2;
            print_error(inf, "Illegal number: ");
            _eputs(inf->argv[1]);
            _eputschar('\n');
            return (1);
        }
        inf->err_len = _erratoi(inf->argv[1]);
        return (-2);
    }
    inf->err_len = -1;
    return (-2);
}

/**
 * _mcd - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *       constant function prototype.
 * Return: Always 0
 */

int _mcd(info_t *inf)
{
    char *s, *di, buf[1024];
    int chdi_ret;

    s = getcwd(buf, 1024);
    if (!s)
    {
        _puts("TODO: >>getcwd failure emsg here<<\n");
    }
    if (!inf->argv[1])
    {
        di = _getenv(inf, "HOME=");
        if (!di)
        {
            chdi_ret = chdir((di = _getenv(inf, "PWD=")) ? di : "/"); /* TODO: what should this be? */
        }
        else
        {
            chdi_ret = chdir(di);
        }
    }
    else if (_strcmp(inf->argv[1], "-") == 0)
    {
        if (!_getenv(inf, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
        chdi_ret = chdir((di = _getenv(inf, "OLDPWD=")) ? di : "/"); /* TODO: what should this be? */
    }
    else
    {
        chdi_ret = chdir(inf->argv[1]);
    }
    if (chdi_ret == -1)
    {
        print_error(inf, "can't cd to ");
        _eputs(inf->argv[1]), _eputschar('\n');
    }
    else
    {
        _setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
        _setenv(inf, "PWD", getcwd(buf, 1024));
    }
    return (0);
}

/**
 * _mhelp - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *       constant function prototype.
 * Return: Always 0
 */

int _mhelp(info_t *inf)
{
    char **arg_arr;
    arg_arr = inf->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
    {
        _puts(*arg_arr);
    }
    return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @st: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *inf, char *st)
{
    char *p, c;
    int ret;

    p = _strchr(st, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = del_node_at_index(&(inf->alias), get_node_index(inf->alias, node_starts_with(inf->alias, st, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
/**
 * _mhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *       constant function prototype.
 * Return: Always 0
 */

int _mhistory(info_t *inf)
{
    print_list(inf->hist);
    return (0);
}