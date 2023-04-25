#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/**
 * struct tokenize_cmd_ops - commands and logical ops tokens
 * @cmd_tokens: commands tokens
 * @ops_tokens: logical ops tokens
*/
typedef struct tokenize_cmd_ops
{
	char **cmd_tokens;
	char **ops_tokens;
} cmd_ops;

extern char **environ;

int contains_log_operator(char *str);
void trunc_comment(char *str);
size_t print_list(const list_t *h);
size_t list_len(const list_t *h);
void _puts(char *str);
list_t *add_node(list_t **head, const char *str);
void newputs(char *str);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);
void free_allocated_memory(list_t *head, char **strs);
char *_getenv(const char *name);
list_t *path_list();
void print_dirs_in_path(void);
char **str_into_tokens(const char *str, char delim, list_t *head);
int has_same_key(char *str, const char *substr);
char *get_value(char *str);
unsigned int key_len(char *str);
int path_exist(const char *str);
int end_with_forward_slash(char *str);
int has_forward_slash(char *str);
char *check_path(char *first_arg, char **dirs, list_t *head);
int _strlen(const char *s);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
int _unsetenv(const char *name);
int _atoi(char *s);
int is_all_digits(char *s);
int _setenv(const char *name, const char *value, int overwrite);
char *_strncpy(char *dest, char *src, int n);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
int _putchar(char c);
int built_in(char *str, char **builtin);
int count_strs(char **strs);
char *itostr(int n);
int num_of_digits(unsigned int num);
int _pow(int base, int exp);
char **store_str_ptrs(const list_t *h, char **ptrs_to_str);
void interpret_dollar(char **str, int status);
void create_child_process(int *status, char **argv);
void execute_builtin_cmd(char **argv, int *status, char *line, list_t *head_argv, FILE *stream);
void handle_cd(int argv_count, char **argv, int *status);
void handle_exit(int argv_count, char **argv, char *line, list_t *head_argv, FILE *stream);
void handle_setenv(int argv_count, char **argv, int *status);
void handle_unsetenv(int argv_count, char **argv, int *status);
void prompt_user(void);
void free_resources(char *line, list_t *head_argv, char **argv, FILE *stream);
cmd_ops *parse_logical_ops(char *str);
int starts_with_semicolon(char *str);
int has_consecutive_semicolon(char *str);
char **parse_semicolon(char *str, list_t *head);
void handle_error(char *str_1, char *str_2, int *status);
void set_old_new_pwd(char *old_dir, char *new_dir, int *status);
void handle_usage_error(char *str, int *status);

#endif
