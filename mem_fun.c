#include "shell.h"

/**
 * _memset - function fill the first @n bytes of the memory area pointed
 * to by @s with the constant byte @b
 *
 * @n: bytes of the memory area pointed to by @s
 *
 * @s: with the constant byte @b
 *
 * @b: memory area pointer
 *
 * Return: a pointer to the memory area @s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}

	return (s);
}

/**
 * ffree - frees a string of strings
 *
 * @hh: string of strings
 *
 * Return: None
 */

void ffree(char **hh)
{
	char **b = hh;

	if (!hh)
	{
		return;
	}
	while (*hh)
	{
		free(*hh++);
	}
	free(b);
}

/**
 * _realloc - reallocates a block of memory
 *
 * @pt: pointer to previous malloc'ated block
 * @old: byte size of previous block
 * @new: byte size of new block
 *
 * Return: pt
 */

void *_realloc(void *pt, unsigned int old, unsigned int new)
{
	char *p;

	if (!pt)
	{
		return (malloc(new));
	}
	if (!new)
	{
		return (free(pt), NULL);
	}
	if (new == old)
	{
		return (pt);
	}
	p = malloc(new);
	if (!p)
	{
		return (NULL);
	}
	old = old < new ? old : new;
	while (old)
	{
		p[old] = ((char *)pt)[old];
	}
	free(pt);
	return (p);
}

/**
 * bfree - frees a pointer and NULLs the address
 *
 * @pt: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0
 */

int bfree(void **pt)
{
	if (!pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
