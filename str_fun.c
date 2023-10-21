#include "shell.h"

/**
 * _strcmp - compare 2 string
 * @s1: string
 *
 * @s2: strmp
 *
 * Return: int
 */

int _strcmp(char *s1, char *s2)
{
	while (((*s1 != '\0') && (*s2 != '\0')) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
	{
		return (0);
	}

	else
	{
		return (*s1 - *s2);
	}
}
/**
 * starts_with - checks if needle starts with haystack
 * @hay: string to search
 * @needl: the substring to find
 *
 * Return: address of next char of hay of NULL
 */
char *starts_with(const char *hay, const char *needl)
{
	while (*needl)
	{
		if (*needl++ != *hay++)
		{
			return (NULL);
		}
	}
	return ((char *)hay);
}

/**
 * _strcat - concat 2 string
 * @dest:char
 * @src:char
 * Return:char
 */

char *_strcat(char *dest, char *src)
{
	char *s = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (s);
}

/**
 * _strlen - function that returns the length of a string.
 * @s : s is a character
 * Return: value is i
 */

int _strlen(const char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
