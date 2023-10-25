#include "shell.h"
/**
 * dec_Printing - displays decimal
 * @input: input
 * @fd: description of file
 * Return: chars No.
 */
int dec_Printing(int input, int fd)
{
	int (*__putchar)(char) = our_CharPut;
	unsigned int Abs, Cr;
	int ind, C = 0;

	if (fd == STDERR_FILENO)
		__putchar = our_Eputchar;
	if (input < 0)
	{
		Abs = -input;
		__putchar('-');
		C++;
	}
	else
		Abs = input;
	Cr = Abs;
	for (ind = 1000000000; ind > 1; ind /= 10)
	{
		if (Abs / ind)
		{
			__putchar('0' + Cr / ind);
			C++;
		}
		Cr %= ind;
	}
	__putchar('0' + Cr);
	C++;
	return (C);
}
/**
 * obt_Environ - obtains the environ
 * @f: struct
 * Return: zero
 */
char **obt_Environ(type_info *f)
{
	if (!f->environ || f->env_changed)
	{
		f->environ = string_from_list(f->env);
		f->env_changed = 0;
	}
	return (f->environ);
}
/**
 * our_Envunsetting - unset the value of environment
 * @f: struct
 * @v: variable
 *  Return: one or zero
 */
int our_Envunsetting(type_info *f, char *v)
{
	size_t index = 0;
	char *ptr;
	type_List *n = f->env;

	if (!n || !v)
		return (0);
	while (n)
	{
		ptr = pointOfSt(n->str, v);
		if (ptr && *ptr == '=')
		{
			f->env_changed = indnode_Rem(&(f->env), index);
			index = 0;
			n = f->env;
			continue;
		}
		n = n->next;
		index++;
	}
	return (f->env_changed);
}
/**
 * our_Envsetting - set the value of environ
 * @f: struct
 * @v: variable
 * @vu: value
 *  Return: zero
 */
int our_Envsetting(type_info *f, char *v, char *vu)
{
	type_List *N;
	char *str;
	char *BF = NULL;

	if (!v || !vu)
		return (0);
	BF = malloc(our_lengthstr(v) + our_lengthstr(vu) + 2);
	if (!BF)
		return (1);
	our_CpyStr(BF, v);
	our_catStr(BF, "=");
	our_catStr(BF, vu);
	N = f->env;
	while (N)
	{
		str = pointOfSt(N->str, v);
		if (str && *str == '=')
		{
			free(N->str);
			N->str = BF;
			f->env_changed = 1;
			return (0);
		}
		N = N->next;
	}
	creat_EnNode(&(f->env), BF, 0);
	free(BF);
	f->env_changed = 1;
	return (0);
}
/**
 * f_setting - info setting
 * @f: struct
 * @arags: array of args
 */
void f_setting(type_info *f, char **arags)
{
	int index = 0;

	f->fname = arags[0];
	if (f->arg)
	{
		f->argv = wfromstr(f->arg, " \t");
		if (!f->argv)
		{
			f->argv = malloc(sizeof(char *) * 2);
			if (f->argv)
			{
				f->argv[0] = our_DupStr(f->arg);
				f->argv[1] = NULL;
			}
		}
		for (index = 0; f->argv && f->argv[index]; index++)
			;
		f->argc = index;
		alias_REPLACING(f);
		VarReplacing(f);
	}
}
