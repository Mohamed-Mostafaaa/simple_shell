#ifndef ______SHELL______H______
#define ______SHELL______H______

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define ReadBufSize 1024
#define WriteBufSize 1024
#define BufFlush -1
#define CmdNorm 0
#define CmdOr 1
#define CmdAnd 2
#define CmdChain 3
#define ConvertLowercase 1
#define UnsignedConvert 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define FileHist ".simple_shell_history"
#define MaxHist 4096
extern char **environ;

/**
 * struct strList - list
 * @num: number
 * @str: string
 * @next: next
 */

typedef struct strList
{
	int num;
	char *str;
	struct strList *next;
} type_List;
/**
 * struct infoPass - Huge List
 * @arg: argument
 * @argv: vector
 * @path: path
 * @argc: Number of args
 * @line_count: Number of errors
 * @err_num: error
 * @linecount_flag: flage
 * @fname: name of file
 * @env: list
 * @environ: environment
 * @history: history
 * @alias: alias
 * @env_changed: new environ
 * @status: status
 * @cmd_buf: BF cmd
 * @cmd_buf_type: type BF cmd
 * @readfd: file description
 * @histcount: count of history
 */

typedef struct infoPass
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	type_List *env;
	type_List *history;
	type_List *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} type_info;
#define InitInfo                                                                \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}
/**
 * struct Built - all builtin functions
 * @type: flage
 * @func: fun
 */
typedef struct Built
{
	char *type;
	int (*func)(type_info *);
} TableBuilt;

int our_lengthstr(char *);
int our_compStr(char *, char *);
char *pointOfSt(const char *, const char *);
char *our_catStr(char *, char *);
char *our_CpyStr(char *, char *);
char *our_DupStr(const char *);
void our_FPuts(char *);
int our_CharPut(char);
char *our_Strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *our_Strch(char *, char);
char **wfromstr(char *, char *);
char **wfromstr2(char *, char);
char *our_Memset(char *, char, unsigned int);
void ourFreeF(char **);
void *our_Realloc(void *, unsigned int, unsigned int);
int ourFreeB(void **);
int checkAct(type_info *);
int checkDel(char, char *);
int check_alpha(int);
int our_atoi(char *);
int our_Eratoi(char *);
void Er_Printing(type_info *, char *);
int dec_Printing(int, int);
char *num_converting(long int, int, int);
void Com_Removing(char *);
int our_Ex(type_info *);
int our_Cd(type_info *);
int our_Help(type_info *);
int our_Hist(type_info *);
int our_Alias(type_info *);
ssize_t obtain_inputtting(type_info *);
int our_Getline(type_info *, char **, size_t *);
void HandlerSigin(int);
void f_clearing(type_info *);
void f_setting(type_info *, char **);
void f_freeing(type_info *, int);
char *obtain_Env(type_info *, const char *);
int our_Env(type_info *);
int our_env_setting(type_info *);
int our_env_unsetting(type_info *);
int Env_list_Pop(type_info *);
char **obt_Environ(type_info *);
int our_Envunsetting(type_info *, char *);
int our_Envsetting(type_info *, char *, char *);
char *obt_FHist(type_info *info);
int Hist_Writing(type_info *info);
int Hist_reading(type_info *info);
int creat_ListHist(type_info *info, char *buf, int linecount);
int Hist_Renumbering(type_info *info);
type_List *creat_Lnode(type_List **, const char *, int);
type_List *creat_EnNode(type_List **, const char *, int);
size_t ListStr_printing(const type_List *);
int indnode_Rem(type_List **, unsigned int);
void alllist_Freeing(type_List **);
size_t length_List(const type_List *);
char **string_from_list(type_List *);
size_t displays_List(const type_List *);
int alias_setting(type_info *, char *);
ssize_t BF_reading(type_info *, char *, size_t *);
ssize_t BF_inputting(type_info *, char **, size_t *);
int strREPLACING(char **, char *);
int mHSH(type_info *, char **);
int built_Finder(type_info *);
void cmdFinder(type_info *);
void cmdForking(type_info *);
int check_cmd(type_info *, char *);
char *chDuplicate(char *, int, int);
char *pathFinder(type_info *, char *, char *);
int loophsh(char **);
void our_Eputs(char *);
int our_Eputchar(char);
int decrF_Put(char c, int fd);
int descF_Puts(char *str, int fd);
type_List *stNode_by(type_List *, char *, char);
ssize_t obtain_IN(type_List *, type_List *);
int check_the_chain(type_info *, char *, size_t *);
void chainCHECK(type_info *, char *, size_t *, size_t, size_t);
int alias_REPLACING(type_info *);
int VarReplacing(type_info *);
int alias_unsetting(type_info *, char *);
int alias_printing(type_List *);

#endif
