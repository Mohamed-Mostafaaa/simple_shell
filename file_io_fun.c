#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(info_t *inf)
{
	char *bu, *di;

	di = _getenv(inf, "HOME=");
	if (!di)
	{
		return (NULL);
	}
	bu = malloc(sizeof(char) * (_strlen(di) + _strlen(HIST_FILE) + 2));
	if (!bu)
	{
		return (NULL);
	}
	bu[0] = 0;
	_strcpy(bu, di);
	_strcat(bu, "/");
	_strcpy(bu, HIST_FILE);
	return (bu);
}

/**
 * write_hist - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int write_hist(info_t *inf)
{
	ssize_t fd;

	char *filename = get_hist_file(inf);

	list_t *nod = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nod = inf->hist; nod; nod = node->next)
	{
		_putsfd(nod->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int read_hist(info_t *inf)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(inf);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_list(inf, buf + last, linecount++);
			last = i + 1;
		}
	}
	if (last != i)
		build_hist_list(inf, buf + last, linecount++);
	free(buf);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		del_node_at_index(&(inf->hist), 0);
	renum_hist(inf);
	return (inf->histcount);
}

/**
 * renum_hist - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int renum_hist(info_t *inf)
{
	list_t *nod = inf->hist;

	int i;

	for (i = 0; nod;)
	{
		nod->num = i++;
		nod = nod->next;
	}
	return (inf->histcount = i);
}

/**
 * build_hist_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @bu: buffer
 * @line_count: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_hist_list(info_t *inf, char *bu, int line_count)
{
	list_t *nod = NULL;

	if (inf->hist)
	{
		nod = inf->hist;
	}
	add_node_end(&nod, bu, line_count);

	if (!inf->hist)
	{
		inf->hist = nod;
	}
	return (0);
}
