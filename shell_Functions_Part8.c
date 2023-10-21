#include "shell.h"
/**
 * stNode_by - get prefex starting node
 * @n: head
 * @p: the matched str
 * @charac: char
 * Return: Null or Node
 */
type_List *stNode_by(type_List *n, char *p, char charac)
{
	char *ptr = NULL;

	while (n)
	{
		ptr = pointOfSt(n->str, p);
		if (ptr && ((charac == -1) || (*ptr == charac)))
			return (n);
		n = n->next;
	}
	return (NULL);
}
#include "shell.h"
/**
 * pathFinder - cmd finder
 * @f: struct
 * @stPath: string path
 * @Fcmd: finding cmd
 * Return: complete cmd path
 */
char *pathFinder(type_info *f, char *stPath, char *Fcmd)
{
	int index = 0, PositionC = 0;
	char *cmdPath;

	if (!stPath)
		return (NULL);
	if ((our_lengthstr(Fcmd) > 2) && pointOfSt(Fcmd, "./"))
	{
		if (check_cmd(f, Fcmd))
			return (Fcmd);
	}
	while (1)
	{
		if (!stPath[index] || stPath[index] == ':')
		{
			cmdPath = chDuplicate(stPath, PositionC, index);
			if (!*cmdPath)
				our_catStr(cmdPath, Fcmd);
			else
			{
				our_catStr(cmdPath, "/");
				our_catStr(cmdPath, Fcmd);
			}
			if (check_cmd(f, cmdPath))
				return (cmdPath);
			if (!stPath[index])
				break;
			PositionC = index;
		}
		index++;
	}
	return (NULL);
}
#include "shell.h"
/**
 * mHSH - loop of the main shell
 * @f: struct
 * @arargs: arrays of args
 * Return: zero or one
 */
int mHSH(type_info *f, char **arargs)
{
	ssize_t c = 0;
	int rBuilt = 0;

	while (c != -1 && rBuilt != -2)
	{
		f_clearing(f);
		if (checkAct(f))
			our_FPuts("$ ");
		our_Eputchar(BufFlush);
		c = obtain_inputtting(f);
		if (c != -1)
		{
			f_setting(f, arargs);
			rBuilt = built_Finder(f);
			if (rBuilt == -1)
				cmdFinder(f);
		}
		else if (checkAct(f))
			our_CharPut('\n');
		f_freeing(f, 0);
	}
	Hist_Writing(f);
	f_freeing(f, 1);
	if (!checkAct(f) && f->status)
		exit(f->status);
	if (rBuilt == -2)
	{
		if (f->err_num == -1)
			exit(f->status);
		exit(f->err_num);
	}
	return (rBuilt);
}
#include "shell.h"
/**
 * built_Finder - builtin finder
 * @info: struct
 * Return: -one,zero,one,2
 */
int built_Finder(type_info *info)
{
	int index, rBuilt = -1;
	TableBuilt allbuilt[] = {
		{"exit", our_Ex},
		{"env", our_Env},
		{"help", our_Help},
		{"history", our_Hist},
		{"setenv", our_env_setting},
		{"unsetenv", our_env_unsetting},
		{"cd", our_Cd},
		{"alias", our_Alias},
		{NULL, NULL}
	};
	for (index = 0; allbuilt[index].type; index++)
		if (our_compStr(info->argv[0], allbuilt[index].type) == 0)
		{
			info->line_count++;
			rBuilt = allbuilt[index].func(info);
			break;
		}
	return (rBuilt);
}
#include "shell.h"
/**
 * cmdFinder - cmd finder
 * @f: struct
 */
void cmdFinder(type_info *f)
{
	int n, m;
	char *p = NULL;

	f->path = f->argv[0];
	if (f->linecount_flag == 1)
	{
		f->line_count++;
		f->linecount_flag = 0;
	}
	for (n = 0, m = 0; f->arg[n]; n++)
		if (!checkDel(f->arg[n], " \t\n"))
			m++;
	if (!m)
		return;
	p = pathFinder(f, obtain_Env(f, "PATH="), f->argv[0]);
	if (p)
	{
		f->path = p;
		cmdForking(f);
	}
	else
	{
		if ((checkAct(f) || obtain_Env(f, "PATH=")
					|| f->argv[0][0] == '/') && check_cmd(f, f->argv[0]))
			cmdForking(f);
		else if (*(f->arg) != '\n')
		{
			f->status = 127;
			Er_Printing(f, "not found\n");
		}
	}
}
