#ifndef SHELL_H
#define SHELL_H

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

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
    char *str;
    unsigned int len;
    struct list_s *next;
} list_t;

/* for convert_number */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* memory functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* liststr model */
size_t print_list(const list_t *);
size_t list_len(const list_t *);
list_t *add_node(list_t **, const char *);
list_t *add_node_end(list_t **, const char *);
void free_list(list_t *);

/* more functions */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

int print_d(int input, int);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);

/* string functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* error string functions */
void _eputs(char *);
int _eputschar(char);
int _putfd(char c, int fd);
int _putsfd(char *st, int fd);
