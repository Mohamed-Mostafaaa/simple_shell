#include "shell.h"

/**
 * print_list - check the code for Holberton School students.
 * @h: name of the list
 * Return: the number of nodes.
 */

size_t print_list(const list_t *h)
{
    int count = 0;

    while (h)
    {
        if (h->str == NULL)
        {
            printf("[0] (nil)\n");
        }
        else
        {
            printf("[%d] %s\n", h->len, h->str);
        }
        count++;
        h = h->next;
    }
    return (count);
}

/**
 * list_len - check the code for Holberton School students.
 * @h: name of the list
 * Return: the number of nodes.
 */

size_t list_len(const list_t *h)
{
    int count = 0;

    while (h)
    {
        count++;
        h = h->next;
    }
    return (count);
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

/**
 * add_node - add a new node at beginning of a list_t list.
 * @head: head of a list_t list.
 * @str: value to insert into element.
 * Return: the number of nodes.
 */

list_t *add_node(list_t **head, const char *str)
{
    list_t *add;

    add = malloc(sizeof(list_t));
    if (add == NULL)
        return (NULL);
    add->str = strdup(str);

    add->len = _strlen(str);
    add->next = *head;
    *head = add;

    return (add);
}

/**
 * free_list - Realease the memory allocated for a list
 *
 * @head: A pointer to the first node of the list to free
 */

void free_list(list_t *head)
{
    if (head)
    {
        free_list(head->next);
        if (head->str)
            free(head->str);
        free(head);
    }
}

/**
 * add_node_end - adds a new node to the end of linked list
 * @head: double pointer to a linked list
 * @str: string to add to the new node
 *
 * Return: pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str)
{
    list_t *new, *tmp;

    if (str == NULL)
        return (NULL);
    new = malloc(sizeof(list_t));
    if (new == NULL)
        return (NULL);
    new->str = strdup(str);
    if (new->str == NULL)
    {
        free(new);
        return (NULL);
    }
    new->len = _strlen(new->str);
    new->next = NULL;
    if (*head == NULL)
    {
        *head = new;
        return (new);
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (new);
}