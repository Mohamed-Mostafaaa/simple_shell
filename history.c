#include "shell.h"
/**
 * HandlerSigin - control cc
 * @n_sigin: number signal
 */
void HandlerSigin(__attribute__((unused))int n_sigin)
{
	our_FPuts("\n");
	our_FPuts("$ ");
	our_CharPut(BufFlush);
}
/**
 * obt_FHist - obtains the history
 * @f: struct
 * Return: string
 */
char *obt_FHist(type_info *f)
{
	char *ptr1, *ptr2;

	ptr2 = obtain_Env(f, "HOME=");
	if (!ptr2)
		return (NULL);
	ptr1 = malloc(sizeof(char) * (our_lengthstr(ptr2) +
	 our_lengthstr(FileHist) + 2));
	if (!ptr1)
		return (NULL);
	ptr1[0] = 0;
	our_CpyStr(ptr1, ptr2);
	our_catStr(ptr1, "/");
	our_catStr(ptr1, FileHist);
	return (ptr1);
}
/**
 * Hist_Writing - write the history
 * @f: struct
 * Return: one or its negative
 */
int Hist_Writing(type_info *f)
{
	ssize_t decrF;
	type_List *n = NULL;
	char *nameF = obt_FHist(f);

	if (!nameF)
		return (-1);

	decrF = open(nameF, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(nameF);
	if (decrF == -1)
		return (-1);
	for (n = f->history; n; n = n->next)
	{
		descF_Puts(n->str, decrF);
		decrF_Put('\n', decrF);
	}
	decrF_Put(BufFlush, decrF);
	close(decrF);
	return (1);
}
/**
 * Hist_reading - gets file of history
 * @f: struct
 * Return: zero or counts
 */
int Hist_reading(type_info *f)
{
	ssize_t descF, lengthR, sFile = 0;
	char *BF = NULL, *nameFile = obt_FHist(f);
	int index, end = 0, cLines = 0;
	struct stat str;

	if (!nameFile)
		return (0);
	descF = open(nameFile, O_RDONLY);
	free(nameFile);
	if (descF == -1)
		return (0);
	if (!fstat(descF, &str))
		sFile = str.st_size;
	if (sFile < 2)
		return (0);
	BF = malloc(sizeof(char) * (sFile + 1));
	if (!BF)
		return (0);
	lengthR = read(descF, BF, sFile);
	BF[sFile] = 0;
	if (lengthR <= 0)
		return (free(BF), 0);
	close(descF);
	for (index = 0; index < sFile; index++)
		if (BF[index] == '\n')
		{
			BF[index] = 0;
			creat_ListHist(f, BF + end, cLines++);
			end = index + 1;
		}
	if (end != index)
		creat_ListHist(f, BF + end, cLines++);
	free(BF);
	f->histcount = cLines;
	while (f->histcount-- >= MaxHist)
		indnode_Rem(&(f->history), 0);
	Hist_Renumbering(f);
	return (f->histcount);
}
/**
 * creat_ListHist - creat list of history
 * @f: struct
 * @BF: BUFFER
 * @cLine: countsof line
 * Return: zero
 */
int creat_ListHist(type_info *f, char *BF, int cLine)
{
	type_List *Listn = NULL;

	if (f->history)
		Listn = f->history;
	creat_EnNode(&Listn, BF, cLine);
	if (!f->history)
		f->history = Listn;
	return (0);
}
