#include "shell.h"
/**
 * our_env_setting - set the value of environment
 * @f: struct
 *  Return: zero
 */
int our_env_setting(type_info *f)
{
	if (f->argc != 3)
	{
		our_Eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (our_Envsetting(f, f->argv[1], f->argv[2]))
		return (0);
	return (1);
}
/**
 * our_env_unsetting - delete var of env
 * @f: struct
 * Return: zero
 */
int our_env_unsetting(type_info *f)
{
	int index;

	if (f->argc == 1)
	{
		our_Eputs("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= f->argc; index++)
		our_Envunsetting(f, f->argv[index]);
	return (0);
}
/**
 * Env_list_Pop - list pop
 * @f: struct
 * Return: zero
 */
int Env_list_Pop(type_info *f)
{
	size_t index;
	type_List *n = NULL;

	for (index = 0; environ[index]; index++)
		creat_EnNode(&n, environ[index], 0);
	f->env = n;
	return (0);
}
/**
 * our_Eputs - displays  str
 * @s: string
 */
void our_Eputs(char *s)
{
	int index = 0;

	if (!s)
		return;
	while (s[index] != '\0')
	{
		our_Eputchar(s[index]);
		index++;
	}
}
/**
 * Er_Printing - displays the error
 * @f: struct
 * @erS: the error string
 */
void Er_Printing(type_info *f, char *erS)
{
	our_Eputs(f->fname);
	our_Eputs(": ");
	dec_Printing(f->line_count, STDERR_FILENO);
	our_Eputs(": ");
	our_Eputs(f->argv[0]);
	our_Eputs(": ");
	our_Eputs(erS);
}
