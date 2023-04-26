#ifndef SIMPLE_SHELL_H_
#define SIMPLE_SHELL_H_


#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _isdigit(const char *s);
char *_strdup(const char *s);
int cmp_chars(char str[], const char *delim);
int count_tokens(char *str, char *delim);
int token_len(char *str, char *delim);
int _strncmp(const char *s1, const char *s2, size_t n);
char **_strtok(char *line, char *delim);

/* Error Handlers */
int error_c(char **args, int err);
void insert_spaces(char *old_line, char *new_line);
void free_line(char **line);
void operations(char *line, ssize_t *new_length);
ssize_t newer_length(char *line);
void line_handler(char **line, ssize_t read);
int number_len(int num);
char *_itos(int num);

/* Linkedlist Helpers */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t **head_ptr);
int delete_node_at_index(list_t **head, unsigned int index);
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
ssize_t get_node_index(list_t *head, list_t *node);
size_t list_len(const list_t *h);
size_t print_list(const list_t *h);




/* Input Helpers */
char *get_input(char *vars, int *ex_retrn);
int querry_input(char **args, char **front, int *ex_retrn);
int run_command(char **args, char **front, int *ex_retrn);
int exec_command(int *ex_retrn);
int check_input(char **args);

/*Path Handlers*/
char *get_path(char *command);
char *copy_path(char *path);
list_t *list_paths(char *path);

/*Helpers */
void free_args(char **args, char **front);
char *_pid(void);
char *env_val(char *beginning, int len);
void replace_var(char **args, int *exe_ret);

/*Builtin Handlers */
int (*get_builtin(char *command))(char **args, char **front);
int exit_shell(char **args, char **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/*Builtin Helpers */
void _all(void);
void _alias(void);
void _cd(void);
void shell_exit(void);
void _help(void);
void env_help(void);
void setenv_help(void);
void unsetenv_help(void);
void history_help(void);

/* Alias Builtin */
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
int shell_alias(char **args, char __attribute__((__unused__)) **front);

/*Environmental Builtin */
int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);

/* Environment Handlers*/
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/*Main Helpers*/
void assign_line(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
int cant_open(char *file_path);
int run_file_commands(char *file_path, int *exe_ret);
void signal_handler(int sig);
int execute(char **args, char **front);
int main(int argc, char *argv[]);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*Error Messages*/
char *env_error(char **args);
char *notfound_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);
char *env_error(char **args);
char *notfound_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);

#endif
