#include "shell.h"
/**
 * our_atoi - obtain integer from string
 * @string: string
 * Return: number or zero
 */
int our_atoi(char *string)
{
	unsigned int r = 0;
	int index, s = 1, f = 0, o;

	for (index = 0; string[index] != '\0' && f != 2; index++)
	{
		if (string[index] == '-')
			s *= -1;
		if (string[index] >= '0' && string[index] <= '9')
		{
			f = 1;
			r *= 10;
			r += (string[index] - '0');
		}
		else if (f == 1)
			f = 2;
	}
	if (s == -1)
		o = -r;
	else
		o = r;
	return (o);
}
/**
 * check_alpha - determines alpha
 * @charac: char
 * Return: one or zero
 */
int check_alpha(int charac)
{
	if ((charac >= 'a' && charac <= 'z') || (charac >= 'A' && charac <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * checkAct - checks mode
 * @f: struct
 * Return: one or zero
 */
int checkAct(type_info *f)
{
	return (isatty(STDIN_FILENO) && f->readfd <= 2);
}
/**
 * checkDel - determines delim
 * @charac: char
 * @Delimeter: delim
 * Return: one or zero
 */
int checkDel(char charac, char *Delimeter)
{
	while (*Delimeter)
		if (*Delimeter++ == charac)
			return (1);
	return (0);
}
/**
 * our_Eputchar - standard error printing
 * @charac: chars
 * Return: one or negative one
 */
int our_Eputchar(char charac)
{
	static char BF[WriteBufSize];
	static int index;

	if (charac == BufFlush || index >= WriteBufSize)
	{
		write(2, BF, index);
		index = 0;
	}
	if (charac != BufFlush)
		BF[index++] = charac;
	return (1);
}

