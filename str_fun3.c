#include "shell.h"

/**
 *_strncpy - function that copies a string
 *
 * @src: The source of strings
 * @dest: The destination of the string
 * @n: The length of int
 *
 * Return: pointer to the resulting string dest
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i;

    for (i = 0; i < n && *(src + i); i++)
    {
        *(dest + i) = *(src + i);
    }
    for (; i < n; i++)
    {
        *(dest + i) = '\0';
    }
    return (dest);
}

/**
 * _strncat - concatenates two strings
 *
 * @src: The source of strings
 * @dest: The destination of the string
 * @n: The length of int
 *
 * Return: pointer to the resulting string dest
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;

    for (i = 0; dest[i] != '\0'; i++)
    {
        continue;
    }
    for (j = 0; src[j] != '\0' && j < n; j++)
    {
        dest[i + j] = src[j];
    }
    dest[i + j] = '\0';
    return (dest);
}

/**
 * _strchr - Locate a character in a string.
 * @s: String.
 * @c: Character.
 * Return: The firs occuerrence of hte character in the string or NULL.
 */

char *_strchr(char *s, char c)
{
    int index;

    for (index = 0; s[index] >= '\0'; index++)
    {
        if (s[index] == c)
            return (s + index);
    }

    return ('\0');
}
