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
