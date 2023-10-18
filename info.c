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

void free_info(info_t *, int)
{
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
        inf->argv = strtow
    }
}