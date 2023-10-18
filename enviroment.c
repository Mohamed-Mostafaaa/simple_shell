#include "shell.h"

/**
 * _getenv - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @na: env var name
 *
 * Return: the value
 */

char *_getenv(info_t *inf, const char *na)
{
    list_t *nod = inf->env;
    char *p;

    while (nod)
    {
        p = starts_with(nod->str, na);
        if (p && *p)
        {
            return (p);
        }
        nod = nod->next;
    }
    return (NULL);
}

/**
 * _myenv - prints the current environmoent
 * @inf: Structure containing potential arguments. Used to maintain
 *       counstant function prototype.
 * Return: Always 0
 */

int _myenv(info_t *inf)
{
    print_list_str(inf->env);
    return (0);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always 0
 */
int _mysetenv(info_t *inf)
{
    if (inf->argc != 3)
    {
        _eputs("Incorrect number of arguements\n");
        return (1);
    }
    if (_setenv(info, inf->argv[1], inf->argv[2]))
    {
        return (0);
    }
    return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int _myunsetenv(info_t *inf)
{
    int i = 1;

    if (inf->argc == 1)
    {
        _eputs("Too few arguements.\n");
        return (1);
    }
    while (i <= inf->argc)
    {
        _unsetenv(inf, inf->argv[i]);
        i++;
    }
    return (0);
}

/**
 * pop_env_list - populates env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *       constant function prototype.
 * Return: Always 0
 */

int pop_env_list(info_t *inf)
{
    list_t *nod = NULL;
    size_t i = 0;

    while (environ[i])
    {
        add_node_end(&nod, environ[i], 0);
        i++;
    }
    inf->env = nod;
    return (0);
}

/**
 * get_environ - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

char **get_environ(info_t *inf)
{
    if (!inf->environ || inf->env_change)
    {
        inf->environ = list_to_str(inf->env);
        inf->env_change = 0;
    }
    return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @va: the string env var property
 */

int _unsetenv(info_t *inf, char *va)
{
    list_t *nod = inf->env;
    size_t i = 0;
    char *p;

    if (!nod || !va)
        return (0);

    while (nod)
    {
        p = starts_with(nod->str, va);
        if (p && *p == '=')
        {
            inf->env_change = del_node_at_index(&(inf->env), i);
            i = 0;
            nod = inf->env;
            continue;
        }
        nod = nod->next;
        i++;
    }
    return (inf->env_change);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */

int _setenv(info_t *inf, char *v, char *val)
{
    char *buf = NULL;
    list_t *nod;
    char *p;

    if (!v || !val)
        return (0);

    buf = malloc(_strlen(v) + _strlen(val) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, v);
    _strcat(buf, "=");
    _strcat(buf, val);
    nod = inf->env;
    while (nod)
    {
        p = starts_with(nod->str, v);
        if (p && *p == '=')
        {
            free(nod->str);
            nod->str = buf;
            inf->env_change = 1;
            return (0);
        }
        nod = nod->next;
    }
    add_node_end(&(inf->env), buf, 0);
    free(buf);
    inf->env_change = 1;
    return (0);
}