#include "shell.h"

/**
 * sigintHand - blocks ctrl-C
 * @signum: the signal number
 *
 * Return: void
 */

void sigintHand(__attribute__((unused)) int signum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * input_buf - buffers chained commands
 * @inf: parameter struct
 * @bu: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *inf, char **bu, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*bu);
		*bu = NULL;
		signal(SIGINT, sigintHand);
#if USE_GETLINE
		r = getline(bu, &len_p, stdin);
#else
		r = _getline(inf, bu, &len_p);
#endif
		if (r > 0)
		{
			if ((*bu)[r - 1] == '\n')
			{
				(*bu)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			inf->linecount_flag = 1;
			remove_comments(*bu);
			build_hist_list(inf, *bu, inf->histcount++);
			if (_strchr(*buf, ';')) /* is this a command chain? */
			{
				*len = r;
				inf->cmd_buf = bu;
			}
		}
	}
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @pt: address of pointer to buffer, preallocated or NULL
 * @leng: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int _getline(info_t *inf, char **pt, size_t *leng)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pt;
	if (p && leng)
		s = *leng;
	if (i == len)
		i = len = 0;
	r = read_buf(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (leng)
		*leng = s;
	*pt = p;
	return (s);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */

ssize_t get_input(info_t *inf)
{
	static char *bu; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(inf, &bu, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = bu + i;

		check_chain(inf, bu, &j, i, len);
		while (j < len)
		{
			if (is_chain(inf, bu, &j))
			{
				break;
			}
			j++;
		}

		i = j + 1;
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @inf: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t read_buf(info_t *inf, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
	{
		return (0);
	}
	r = read(inf->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
	{
		*i = r;
	}
	return (r);
}
