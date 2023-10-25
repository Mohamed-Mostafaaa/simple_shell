#include "shell.h"
/**
 * our_Ex - outs from shell
 * @f: struct
 * Return: satatus of exit
 */
int our_Ex(type_info *f)
{
	int chEx;

	if (f->argv[1])
	{
		chEx = our_Eratoi(f->argv[1]);
		if (chEx == -1)
		{
			f->status = 2;
			Er_Printing(f, "Illegal number: ");
			our_Eputs(f->argv[1]);
			our_Eputchar('\n');
			return (1);
		}
		f->err_num = our_Eratoi(f->argv[1]);
		return (-2);
	}
	f->err_num = -1;
	return (-2);
}
/**
 * our_Cd - to get the directory
 * @f: structu
 * Return: zero
 */
int our_Cd(type_info *f)
{
	int rChDr;
	char *ptr, *d, BF[1024];

	ptr = getcwd(BF, 1024);
	if (!ptr)
		our_FPuts("TODO: >>getcwd failure emsg here<<\n");
	if (!f->argv[1])
	{
		d = obtain_Env(f, "HOME=");
		if (!d)
			rChDr =
				chdir((d = obtain_Env(f, "PWD=")) ? d : "/");
		else
			rChDr = chdir(d);
	}
	else if (our_compStr(f->argv[1], "-") == 0)
	{
		if (!obtain_Env(f, "OLDPWD="))
		{
			our_FPuts(ptr);
			our_CharPut('\n');
			return (1);
		}
		our_FPuts(obtain_Env(f, "OLDPWD=")), our_CharPut('\n');
		rChDr =
			chdir((d = obtain_Env(f, "OLDPWD=")) ? d : "/");
	}
	else
		rChDr = chdir(f->argv[1]);
	if (rChDr == -1)
	{
		Er_Printing(f, "can't cd to ");
		our_Eputs(f->argv[1]), our_Eputchar('\n');
	}
	else
	{
		our_Envsetting(f, "OLDPWD", obtain_Env(f, "PWD="));
		our_Envsetting(f, "PWD", getcwd(BF, 1024));
	}
	return (0);
}
/**
 * our_Help - help function
 * @f: struct
 * Return: zero
 */
int our_Help(type_info *f)
{
	char **arArgs;

	arArgs = f->argv;
	our_FPuts("help call works. Function not yet implemented \n");
	if (0)
		our_FPuts(*arArgs);
	return (0);
}
/**
 * our_Hist - like history function
 * @f: struct
 *  Return: Always 0
 */
int our_Hist(type_info *f)
{
	displays_List(f->history);
	return (0);
}
/**
 * alias_unsetting - obtains string from alias
 * @f: struct
 * @ptr: string
 * Return: zero or one
 */
int alias_unsetting(type_info *f, char *ptr)
{
	int R;
	char *ptrs, charac;

	ptrs = our_Strch(ptr, '=');
	if (!ptrs)
		return (1);
	charac = *ptrs;
	*ptrs = 0;
	R = indnode_Rem(&(f->alias),
		obtain_IN(f->alias, stNode_by(f->alias, ptr, -1)));
	*ptrs = charac;
	return (R);
}
