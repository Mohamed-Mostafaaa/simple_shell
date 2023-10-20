#include "shell.h"

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
