#include "shell.h"
/**
 * strREPLACING - used to replace thestring
 * @old: the old
 * @new: the new
 * Return: one or zero
 */
int strREPLACING(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

