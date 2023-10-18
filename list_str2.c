#include "shell.h"

/**
 * node_starts_with - returns node whose string starts with prefix
 * @nod: pointer to list head
 * @pre: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *node_starts_with(list_t *nod, char *pre, char c)
{
    char *p = NULL;

    while (nod)
    {
        p = starts_with(nod->str, pre);
        if (p && ((c == -1) || (*p == c)))
            return (nod);
        nod = nod->next;
    }
    return (NULL);
}

/**
 * del_node_at_index - deletes node at given index
 * @h: address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int del_node_at_index(list_t **h, unsigned int ind)
{
    list_t *nod, *prev_nod;
    unsigned int i = 0;

    if (!h || !*h)
        return (0);

    if (!ind)
    {
        nod = *h;
        *h = (*h)->next;
        free(nod->str);
        free(nod);
        return (1);
    }
    nod = *h;
    while (nod)
    {
        if (i == ind)
        {
            prev_nod->next = nod->next;
            free(nod->str);
            free(nod);
            return (1);
        }
        i++;
        prev_nod = nod;
        nod = nod->next;
    }
    return (0);
}

/**
 * get_node_index - gets the index of a node
 * @h: pointer to list head
 * @nod: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *h, list_t *nod)
{
    size_t i;
    for (i = 0; h; i++)
    {
        if (h == nod)
        {
            return (i);
        }
        h = h->next;
    }
    return (-1);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */

size_t print_list_str(const list_t *head)
{
    size_t i;

    for (i = 0; head; i++)
    {
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
    }
    return (i);
}

/**
 * free_list - Realease the memory allocated for a list
 *
 * @h: A pointer to the first node of the list to free
 */

void free_list(list_t *h)
{
    if (h)
    {
        free_list(h->next);
        if (h->str)
            free(h->str);
        free(h);
    }
}
