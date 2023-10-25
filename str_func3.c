#include "shell.h"
/**
 **our_Strncpy - likes strncpy
 *@d: given destination
 *@sc: given source
 *@nB: number of Bytes
 *Return: string conc
 */
char *our_Strncpy(char *d, char *sc, int nB)
{
	char *str = d;
	int m, k;

	m = 0;
	while (sc[m] != '\0' && m < nB - 1)
	{
		d[m] = sc[m];
		m++;
	}
	if (m < nB)
	{
		k = m;
		while (k < nB)
		{
			d[k] = '\0';
			k++;
		}
	}
	return (str);
}
/**
 **_strncat - strings will concat
 *@d: 1st string
 *@ss: 2nd string
 *@Bn: Bytes number
 *Return: full string
 */
char *_strncat(char *d, char *ss, int Bn)
{
	char *s = d;
	int m, k;

	m = 0;
	k = 0;
	while (d[m] != '\0')
		m++;
	while (ss[k] != '\0' && k < Bn)
	{
		d[m] = ss[k];
		m++;
		k++;
	}
	if (k < Bn)
		d[m] = '\0';
	return (s);
}
/**
 **our_Strch - search for char
 *@string: any string
 *@charac: char in string
 *Return: the location of char
 */
char *our_Strch(char *string, char charac)
{
	do {
		if (*string == charac)
			return (string);
	} while (*string++ != '\0');
	return (NULL);
}
/**
 * f_clearing - info clearing
 * @f: struct
 */
void f_clearing(type_info *f)
{
	f->arg = NULL;
	f->argv = NULL;
	f->path = NULL;
	f->argc = 0;
}
/**
 * Hist_Renumbering - history renumbering
 * @f: struct
 * Return: counts
 */
int Hist_Renumbering(type_info *f)
{
	type_List *ListN = f->history;
	int index = 0;

	while (ListN)
	{
		ListN->num = index++;
		ListN = ListN->next;
	}
	return (f->histcount = index);
}

