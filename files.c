#include "shell.h"
/**
 * f_freeing - used to free info list
 * @f: struct
 * @a: All list
 */
void f_freeing(type_info *f, int a)
{
	ourFreeF(f->argv);
	f->argv = NULL;
	f->path = NULL;
	if (a)
	{
		if (!f->cmd_buf)
			free(f->arg);
		if (f->env)
			alllist_Freeing(&(f->env));
		if (f->history)
			alllist_Freeing(&(f->history));
		if (f->alias)
			alllist_Freeing(&(f->alias));
		ourFreeF(f->environ);
			f->environ = NULL;
		ourFreeB((void **)f->cmd_buf);
		if (f->readfd > 2)
			close(f->readfd);
		our_CharPut(BufFlush);
	}
}
/**
 * BF_inputting - input the BUFFER
 * @ff: struct
 * @BF: BUFFER
 * @length: variable length
 * Return: inputed bytes
 */
ssize_t BF_inputting(type_info *ff, char **BF, size_t *length)
{
	size_t lengthP = 0;
	ssize_t readed = 0;

	if (!*length)
	{
		free(*BF);
		*BF = NULL;
		signal(SIGINT, HandlerSigin);
#if USE_GETLINE
		readed = getline(BF, &lengthP, stdin);
#else
		readed = our_Getline(ff, BF, &lengthP);
#endif
		if (readed > 0)
		{
			if ((*BF)[readed - 1] == '\n')
			{
				(*BF)[readed - 1] = '\0';
				readed--;
			}
			ff->linecount_flag = 1;
			Com_Removing(*BF);
			creat_ListHist(ff, *BF, ff->histcount++);
			{
				*length = readed;
				ff->cmd_buf = BF;
			}
		}
	}
	return (readed);
}
/**
 * obtain_inputtting - obtains the input
 * @f: struct
 * Return: readed number of bytes
 */
ssize_t obtain_inputtting(type_info *f)
{
	static size_t m, k, length;
	char **BFP = &(f->arg), *p;
	static char *BF;
	ssize_t read = 0;

	our_CharPut(BufFlush);
	read = BF_inputting(f, &BF, &length);
	if (read == -1)
		return (-1);
	if (length)
	{
		k = m;
		p = BF + m;
		chainCHECK(f, BF, &k, m, length);
		while (k < length)
		{
			if (check_the_chain(f, BF, &k))
				break;
			k++;
		}
		m = k + 1;
		if (m >= length)
		{
			m = length = 0;
			f->cmd_buf_type = CmdNorm;
		}
		*BFP = p;
		return (our_lengthstr(p));
	}
	*BFP = BF;
	return (read);
}
/**
 * BF_reading - BUFFER Reading
 * @f: struct
 * @BF: BUFFER
 * @s: the size
 * Return: readedbytes
 */
ssize_t BF_reading(type_info *f, char *BF, size_t *s)
{
	ssize_t readed = 0;

	if (*s)
		return (0);
	readed = read(f->readfd, BF, ReadBufSize);
	if (readed >= 0)
		*s = readed;
	return (readed);
}
/**
 * our_Getline - obtains the lie
 * @f: struct
 * @str: pointer
 * @l: length
 * Return: size
 */
int our_Getline(type_info *f, char **str, size_t *l)
{
	static size_t index, length;
	size_t m;
	char *ptr1 = NULL, *ptr2 = NULL, *c;
	ssize_t read = 0, size = 0;
	static char BF[ReadBufSize];

	ptr1 = *str;
	if (ptr1 && l)
		size = *l;
	if (index == length)
		index = length = 0;
	read = BF_reading(f, BF, &length);
	if (read == -1 || (read == 0 && length == 0))
		return (-1);
	c = our_Strch(BF + index, '\n');
	m = c ? 1 + (unsigned int)(c - BF) : length;
	ptr2 = our_Realloc(ptr1, size, size ? size + m : m + 1);
	if (!ptr2)
		return (ptr1 ? free(ptr1), -1 : -1);
	if (size)
		_strncat(ptr2, BF + index, m - index);
	else
		our_Strncpy(ptr2, BF + index, m - index + 1);
	size += m - index;
	index = m;
	ptr1 = ptr2;
	if (l)
		*l = size;
	*str = ptr1;
	return (size);
}
