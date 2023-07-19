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

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;
/**
 * struct liststr - singly linked list
 * @n: number input
 * @s: pointer to char
 * @next: pointer to the next node
 */
typedef struct liststr
{
	int n;
	char *s;
	struct liststr *next;
} list_t
/**
 * struct passinfo - singly linked list
 * @arg: string 
 * @argc: argument count
 * @argv: array of arguments
 * @alias: pointer to a member of list_t
 * @path: 
 * @history: pointer to a member of list_t
 * @env: pointer to member of list_t
 * @environ: double pointer to string having environment variables
 * @env_change: flag to track changes in the environment
 * @err_num: stores error number or code
 * @line_count_flag: flag for line counting
 * @status: stores status code
 * @fname: stores file name
 * @hist_count: counts the history line number
 * @readfd: reads file from the line input
 * @cmd_buff_type: 
 * @cmd_buff: address of pointer to cmd_buff
 */
typedef struct passinfo
{
	char *arg;
	int argc;
	char **argv;
	list_t alias;
	char *path;
	list_t *history;
	list_t *env;
	char **environ;
	int env_change;
	int err_num;
	int line_count_flag;
	int status;
	char fname;

	int hist_count;
	int readfd;
	int cmd_buff_type;
	char **cmd_buff;
} info_t;

#define INFO_INIT \
{NULL, O, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL, 0, 0, 0, NULL}
/**
 * struct built_in - structure that has built_in functions in it
 * @type: strng representing the type of built in command
 * @func: function pointrr to the corresponding built in command
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} built_ins;

/* my_loopsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* my_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* my loop_hsh.c */
int loophsh(char **);

/* my_errors.c */
void eputs(char *);
int eputchar(char *);
int putfd(char c, int fd);
int putsfd(char *s, int fd);

/* my_string.c */
char _strcmp(char *, char *);
char _strlen(char *);
char *start_with(const char *, const char *);
char *_strcat(char *, char *);

/* my strings.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int *_putchar(char);

/* my_exits.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char strchr(char *, char *);

/* my_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* my_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* my_memory.c */
int bfree(void **);

/* my atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* my_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* my_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* my_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* my_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* my_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* my_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* my_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* my_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* my_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* my_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* my_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
