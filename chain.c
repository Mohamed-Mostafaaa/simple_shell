#include "shell.h"
/**
 * our_DupStr - like strdup function
 * @ptr: string
 * Return: address
 */
char *our_DupStr(const char *ptr)
{
	char *pt;
	int l = 0;

	if (ptr == NULL)
		return (NULL);
	while (*ptr++)
		l++;
	pt = malloc(sizeof(char) * (l + 1));
	if (!pt)
		return (NULL);
	for (l++; l--;)
		pt[l] = *--ptr;
	return (pt);
}
/**
 * our_CharPut - displays standard output
 * @charac: char
 * Return: one or its negative
 */
int our_CharPut(char charac)
{
	static char BF[WriteBufSize];
	static int index;

	if (charac == BufFlush || index >= WriteBufSize)
	{
		write(1, BF, index);
		index = 0;
	}
	if (charac != BufFlush)
		BF[index++] = charac;
	return (1);
}
/**
 * **wfromstr2 - converts string to words
 * @ptr: string
 * @Delim: delim
 * Return: address
 */
char **wfromstr2(char *ptr, char Delim)
{
	char **string;
	int l, m, n, o, wn = 0;

	if (ptr == NULL || ptr[0] == 0)
		return (NULL);
	for (l = 0; ptr[l] != '\0'; l++)
		if ((ptr[l] != Delim && ptr[l + 1] == Delim) ||
				    (ptr[l] != Delim && !ptr[l + 1]) || ptr[l + 1] == Delim)
			wn++;
	if (wn == 0)
		return (NULL);
	string = malloc((1 + wn) * sizeof(char *));
	if (!string)
		return (NULL);
	for (l = 0, m = 0; m < wn; m++)
	{
		while (ptr[l] == Delim && ptr[l] != Delim)
			l++;
		n = 0;
		while (ptr[l + n] != Delim && ptr[l + n] && ptr[l + n] != Delim)
			n++;
		string[m] = malloc((n + 1) * sizeof(char));
		if (!string[m])
		{
			for (n = 0; n < m; n++)
				free(string[n]);
			free(string);
			return (NULL);
		}
		for (o = 0; o < n; o++)
			string[m][o] = ptr[l++];
		string[m][o] = 0;
	}
	string[m] = NULL;
	return (string);
}
/**
 * check_the_chain - check chains
 * @f: struct
 * @BF: BUFFER Chain
 * @ptr: pointer
 * Return: one or zero
 */
int check_the_chain(type_info *f, char *BF, size_t *ptr)
{
	size_t index = *ptr;

	if (BF[index] == '|' && BF[index + 1] == '|')
	{
		BF[index] = 0;
		index++;
		f->cmd_buf_type = CmdOr;
	}
	else if (BF[index] == '&' && BF[index + 1] == '&')
	{
		BF[index] = 0;
		index++;
		f->cmd_buf_type = CmdAnd;
	}
	else if (BF[index] == ';')
	{
		BF[index] = 0;
		f->cmd_buf_type = CmdChain;
	}
	else
		return (0);
	*ptr = index;
	return (1);
}
/**
 * chainCHECK - chain checked
 * @f: struct
 * @BF: BUFFER
 * @ptr: pointer
 * @index: BUFFER Position
 * @l: BUFFER Length
 */
void chainCHECK(type_info *f, char *BF, size_t *ptr, size_t index, size_t l)
{
	size_t in = *ptr;

	if (f->cmd_buf_type == CmdAnd)
	{
		if (f->status)
		{
			BF[index] = 0;
			in = l;
		}
	}
	if (f->cmd_buf_type == CmdOr)
	{
		if (!f->status)
		{
			BF[index] = 0;
			in = l;
		}
	}
	*ptr = in;
}

