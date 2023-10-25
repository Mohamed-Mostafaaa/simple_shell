#include "shell.h"
/**
 * alias_setting - obtains string
 * @f: struct
 * @s: string
 * Return: zero or one
 */
int alias_setting(type_info *f, char *s)
{
	char *str;

	str = our_Strch(s, '=');
	if (!str)
		return (1);
	if (!*++str)
		return (alias_unsetting(f, s));
	alias_unsetting(f, s);
	return (creat_EnNode(&(f->alias), s, 0) == NULL);
}
/**
 * alias_printing - displays string of alias
 * @n: list node
 * Return: zero or one
 */
int alias_printing(type_List *n)
{
	char *ptr1 = NULL, *ptr2 = NULL;

	if (n)
	{
		ptr1 = our_Strch(n->str, '=');
		for (ptr2 = n->str; ptr2 <= ptr1; ptr2++)
		our_CharPut(*ptr2);
		our_CharPut('\'');
		our_FPuts(ptr1 + 1);
		our_FPuts("'\n");
		return (0);
	}
	return (1);
}
/**
 * our_Alias - like alias
 * @f: سtruct
 *  Return: zero
 */
int our_Alias(type_info *f)
{
	int index = 0;
	type_List *n = NULL;
	char *ptr = NULL;

	if (f->argc == 1)
	{
		n = f->alias;
		while (n)
		{
			alias_printing(n);
			n = n->next;
		}
		return (0);
	}
	for (index = 1; f->argv[index]; index++)
	{
		ptr = our_Strch(f->argv[index], '=');
		if (ptr)
			alias_setting(f, f->argv[index]);
		else
			alias_printing(stNode_by(f->alias, f->argv[index], '='));
	}
	return (0);
}
/**
 * our_Env - displays env
 * @f: struct
 * Return: zero
 */
int our_Env(type_info *f)
{
	ListStr_printing(f->env);
	return (0);
}
/**
 * obtain_Env - obtains env value
 * @f: struct
 * @n: name of variable
 * Return: env value
 */
char *obtain_Env(type_info *f, const char *n)
{
	char *ptr;
	type_List *listN = f->env;

	while (listN)
	{
		ptr = pointOfSt(listN->str, n);
		if (ptr && *ptr)
			return (ptr);
		listN = listN->next;
	}
	return (NULL);
}
