#include "shell.h"
/**
 * creat_Lnode - creat new node
 * @h: head
 * @s: string
 * @n: index
 * Return: list size
 */
type_List *creat_Lnode(type_List **h, const char *s, int n)
{
	type_List *nHead;

	if (!h)
		return (NULL);
	nHead = malloc(sizeof(type_List));
	if (!nHead)
		return (NULL);
	our_Memset((void *)nHead, 0, sizeof(type_List));
	nHead->num = n;
	if (s)
	{
		nHead->str = our_DupStr(s);
		if (!nHead->str)
		{
			free(nHead);
			return (NULL);
		}
	}
	nHead->next = *h;
	*h = nHead;
	return (nHead);
}
/**
 * creat_EnNode - creats node at the end
 * @h: head
 * @s: string
 * @n: index
 * Return: list size
 */
type_List *creat_EnNode(type_List **h, const char *s, int n)
{
	type_List *node1, *node2;

	if (!h)
		return (NULL);
	node2 = *h;
	node1 = malloc(sizeof(type_List));
	if (!node1)
		return (NULL);
	our_Memset((void *)node1, 0, sizeof(type_List));
	node1->num = n;
	if (s)
	{
		node1->str = our_DupStr(s);
		if (!node1->str)
		{
			free(node1);
			return (NULL);
		}
	}
	if (node2)
	{
		while (node2->next)
			node2 = node2->next;
		node2->next = node1;
	}
	else
		*h = node1;
	return (node1);
}
/**
 * ListStr_printing - displays the string of the list
 * @head: head
 * Return: list size
 */
size_t ListStr_printing(const type_List *head)
{
	size_t index = 0;

	while (head)
	{
		our_FPuts(head->str ? head->str : "(nil)");
		our_FPuts("\n");
		head = head->next;
		index++;
	}
	return (index);
}
/**
 * string_from_list - gets the string array
 * @h: head
 * Return: string array
 */
char **string_from_list(type_List *h)
{
	type_List *n = h;
	size_t m = length_List(h), k;
	char **ptr1;
	char *ptr2;

	if (!h || !m)
		return (NULL);
	ptr1 = malloc(sizeof(char *) * (m + 1));
	if (!ptr1)
		return (NULL);
	for (m = 0; n; n = n->next, m++)
	{
		ptr2 = malloc(our_lengthstr(n->str) + 1);
		if (!ptr2)
		{
			for (k = 0; k < m; k++)
				free(ptr1[k]);
			free(ptr1);
			return (NULL);
		}

		ptr2 = our_CpyStr(ptr2, n->str);
		ptr1[m] = ptr2;
	}
	ptr1[m] = NULL;
	return (ptr1);
}
/**
 * displays_List - displays component of list
 * @head: head
 * Return: list size
 */
size_t displays_List(const type_List *head)
{
	size_t index = 0;

	while (head)
	{
		our_FPuts(num_converting(head->num, 10, 0));
		our_CharPut(':');
		our_CharPut(' ');
		our_FPuts(head->str ? head->str : "(nil)");
		our_FPuts("\n");
		head = head->next;
		index++;
	}
	return (index);
}
