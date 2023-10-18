#include "shell.h"

/**
 * clr_info - initalizes info_t struct
 * @inf: struct address
 */

void clr_info(info_t *inf)
{
    inf->arg = NULL;
    inf->argv = NULL;
    inf->path = NULL;
    inf->argc = 0;
}

/**
 * free_info - frees info_t struct fields
 * @inf: struct address
 * @al: true if freeing all fields
 */

void free_info(info_t *inf, int al)
{
    ffree(inf->argv);
    inf->argv = NULL;
    inf->path = NULL;
    if (al)
    {
        if (!inf->cmd_buf)
        {
            free(inf->arg);
        }
        if (!inf->env)
        {
            free_list(&(inf->env));
        }
        if (!inf->hist)
        {
            free_list(&(inf->hist));
        }
        if (!inf->alias)
        {
            free_list(&(inf->alias));
        }
        ffree(inf->environ);
        inf->environ = NULL;
        bfree((void **)inf->cmd_buf);
        if (inf->readfd > 2)
        {
            close(inf->readfd);
        }
        _putchar(BUF_FLUSH);
    }
}

/**
 * set_info - initializes info_t struct
 * @inf: struct address
 * @ev: argument vector
 */

void set_info(info_t *inf, char **ev)
{
    int j = 0;

    inf->fname = ev[0];
    if (inf->arg)
    {
        inf->argv = strtow(info->arg, " \t");
        if (!inf->argv)
        {
            inf->argv = malloc(sizeof(char *) * 2);
            if (inf->argv)
            {
                inf->argv[0] = _strdup(inf->arg);
                inf->argv[1] = NULL;
            }
        }
        for (i = 0; inf->argv && inf->argv[i]; i++)
            ;
        inf->argc = i;
        replace_alias(inf);
        replace_vars(inf);
    }
}