#include "shell.h"

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
	{
		return (1);
	}
	c = *p;
	*p = 0;
	ret = del_node_at_index(&(inf->alias), get_node_index(inf->alias,
	node_starts_with(inf->alias, st, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @st: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info_t *inf, char *st)
{
	char *p;

	p = _strchr(st, '=');
	if (!p)
	{
	return (1);
	}
	if (!*++p)
	{
		return (unset_alias(inf, st));
	}

	unset_alias(inf, st);
	return (add_node_end(&(inf->alias), st, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nod: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int print_alias(list_t *nod)
{
	char *p = NULL, *a = NULL;

	if (nod)
	{
		p = _strchr(nod->str, '=');
		for (a = nod->str; a <= p; a++)
		{
			_putchar(*a);
		}
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _malias - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int _malias(info_t *inf)
{
	int i = 0;
	char *p = NULL;
	list_t *nod = NULL;

	if (inf->argc == 1)
	{
		nod = inf->alias;
		while (nod)
		{
			print_alias(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		p = _strchr(inf->argv[i], '=');
		if (p)
		{
			set_alias(inf, inf->argv[i]);
		}
		else
		{
			print_alias(node_starts_with(inf->alias, inf->argv[i], '='));
		}
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
