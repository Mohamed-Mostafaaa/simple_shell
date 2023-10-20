#include "shell.h"

/**
 * _eputs - prints an input string
 * @st: the string to be printed
 *
 * Return: Nothing
 */

void _eputs(char *st)
{
	int i = 0;

	if (!st)
	{
		return;
	}
	while (st[i] != '\0')
	{
		_eputschar(st[i]);
		i++;
	}
}

/**
 * _eputschar (char c) - writes the character c to stderr
 * @c: the character to print
 *
 * Return: On success 1
 * On error, -1 is returned,and errno is set appropriately.
 */

int _eputschar(char c)
{
	static int i;

	static char buf(WRITE_BUF_SIZE);

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}

/**
 * _putfd - write the character c to given fd
 * @c: the character to print
 * @fd: the fileedescreptor to write to
 *
 * Return: On succes1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int i;

	static char buf(WRITE_BUF_SIZE);

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}

/**
 * _putsfd - prints an input string
 * @st: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int _putsfd(char *st, int fd)
{
	int i = 0;

	if (!st)
	{
		return (0);
	}
	while (*st)
	{
		i += _putfd(*st++, fd);
	}
	return (i);
}
