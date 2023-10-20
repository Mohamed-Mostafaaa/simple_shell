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
 * _menv - prints the current environmoent
 * @inf: Structure containing potential arguments. Used to maintain
 *       counstant function prototype.
 * Return: Always 0
 */

int _menv(info_t *inf)
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

