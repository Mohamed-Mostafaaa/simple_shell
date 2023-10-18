#include "shell.h"

/**
 * check_chain - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void check_chain(info_t *inf, char *buf, size_t *p, size_t i, size_t len)
{
    size_t x = *p;

    if (inf->cmd_buf_type == CMD_AND)
    {
        if (inf->stat)
        {
            buf[i] = 0;
            x = len;
        }
    }
    if (inf->cmd_buf_type == CMD_OR)
    {
        if (!inf->stat)
        {
            buf[i] = 0;
            x = len;
        }
    }
    *p = x;
}

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @bu: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(info_t *inf, char *bu, size_t *p)
{
    size_t j = *p;

    if (bu[j] == '|' && bu[j + 1] == '|')
    {
        bu[j] = 0;
        j++;
        inf->cmd_buf_type = CMD_OR;
    }
    else if (bu[j] == '&' && bu[j + 1] == '&')
    {
        bu[j] = 0;
        j++;
        inf->cmd_buf_type = CMD_AND;
    }
    else if (bu[j] == ';') /* found end of this command */
    {
        bu[j] = 0; /* replace semicolon with null */
        inf->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return (0);
    }
    *p = j;
    return (1);
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_alias(info_t *inf)
{
    int i;
    list_t *nod;
    char *p;

    for (i = 0; i < 10; i++)
    {
        nod = node_starts_with(inf->alias, inf->argv[0], '=');
        if (!nod)
        {
            return (0);
        }
        free(inf->argv[0]);
        p = _strchr(nod->str, '=');
        if (!p)
        {
            return (0);
        }
        p = _strdup(p + 1);
        if (!p)
        {
            return (0);
        }
        inf->argv[0] = p;
    }
    return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *inf)
{
    int i = 0;
    list_t *nod;

    for (i = 0; inf->argv[i]; i++)
    {
        if (inf->argv[i][0] != '$' || !inf->argv[i][1])
        {
            continue;
        }
        if (!_strcmp(inf->argv[i], "$?"))
        {
            replace_string(&(inf->argv[i]), _strdup(convert_number(inf->stat, 10, 0)));
            continue;
        }
        if (!_strcmp(inf->argv[i], "$$"))
        {
            replace_string(&(inf->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        nod = node_starts_with(inf->env, &inf->argv[i][1], '=');
        if (nod)
        {
            replace_string(&(inf->argv[i]),
                           _strdup(_strchr(nod->str, '=') + 1));
            continue;
        }
        replace_string(&inf->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
