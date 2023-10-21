#include "shell.h"
/**
 * our_lengthstr - to get the length of string
 * @str: string
 * Return: length
 */
int our_lengthstr(char *str)
{
	int counter = 0;

	if (!str)
		return (0);
	while (*str++)
		counter++;
	return (counter);
}
/**
 * our_compStr - like strcmp function
 * @ptr1: string No.1
 * @ptr2: string No.
 * Return: -1 or 1 or 0
 */
int our_compStr(char *ptr1, char *ptr2)
{
	while (*ptr1 && *ptr2)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
	}
	if (*ptr1 == *ptr2)
		return (0);
	else
		return (*ptr1 < *ptr2 ? -1 : 1);
}
/**
 * pointOfSt - haystack checking
 * @H: checking string
 * @N: the required string
 * Return: pointer
 */
char *pointOfSt(const char *H, const char *N)
{
	while (*N)
		if (*N++ != *H++)
			return (NULL);
	return ((char *)H);
}
/**
 * our_catStr - like strcat function
 * @BD: Buffer destin.
 * @BS: Buffer source
 * Return: address
 */
char *our_catStr(char *BD, char *BS)
{
	char *a = BD;

	while (*BD)
		BD++;
	while (*BS)
		*BD++ = *BS++;
	*BD = *BS;
	return (a);
}
/**
 * our_CpyStr - like strcpy function
 * @BD: Buffer destin.
 * @BS: Buffer source
 * Return: address
 */
char *our_CpyStr(char *BD, char *BS)
{
	int count = 0;

	if ((BD == BS) || (BS == 0))
		return (BD);
	while (BS[count])
	{
		BD[count] = BS[count];
		count++;
	}
	BD[count] = 0;
	return (BD);
}

