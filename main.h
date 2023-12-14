#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} list_ti;

/**
 * struct head_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct head_list_s
{
	char separator;
	struct head_list_s *next;
} head_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(list_ti *darel);
} builtin_t;

/* ai_lcommon.c */
head_list *separate_end(head_list **head, char sep);
void separator_list(head_list **head);
line_list *command_node(line_list **head, char *line);
void f_line_list(line_list **head);

/* ai_lcommonone.c */
r_var *addvar_node(r_var **head, int lvar, char *var, int lval);
void rvariable_list(r_var **head);

/* ai_string.c	 functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_chrstring(char *s, char c);
int _strlength(char *s, char *accept);

/* ai_memory.c */
void _copyinfo(void *newptr, const void *ptr, unsigned int size);
void *_reallocmemo(void *ptr, unsigned int old_size, unsigned int new_size);
char **_redou(char **ptr, unsigned int old_size, unsigned int new_size);

/* ai_string2.c */
char *_dupheapmemo(const char *s);
int _strlen(const char *s);
int compare_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigitstring(const char *s);

/* ai_string3.c */
void reverse_string(char *s);

/* check_error.c */
int repetition_char(char *input, int i);
int syn_error(char *input, int i, char last);
int first_ind_char(char *input, int *i);
void print_syntax_err(list_ti *darel, char *input, int i, int bool);
int check_syntax_err(list_ti *darel, char *input);

/* loop_shell.c */
char *delete_comment(char *in);
void loop_shell(list_ti *darel);

/* read_inp_string.c */
char *read_inp_string(int *i_eof);

/* swap_character.c */
char *swap_character(char *input, int bool);
void add_separatenodes(head_list **head_s, line_list **head_l, char *input);
void go_nextcmd(head_list **list_s, line_list **list_l, list_ti *darel);
int split_cmd(list_ti *darel, char *input);
char **split_line(char *input);

/* replace_variable.c */
void check_env_var(r_var **h, char *in, list_ti *data);
int check_Tvariables(r_var **h, char *in, char *st, list_ti *data);
char *replaces_stinput(r_var **head, char *input, char *new_input, int nlen);
char *replace_variable(char *input, list_ti *darel);

/* gline_cmd.c */
void ass_varline(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t Rinpt_line(char **lineptr, size_t *n, FILE *stream);

/* execution_data.c */
int exec_line_command(list_ti *darel);

/* command_exec.c */
int check_cdir(char *path, int *i);
char *_whichcmd(char *cmd, char **_environ);
int is_execute(list_ti *darel);
int check_error_command(char *dir, list_ti *darel);
int cmd_execute(list_ti *darel);

/* enviro1.c */
char *_envvariable(const char *name, char **_environ);
int _env(list_ti *darel);

/* enviro2.c */
char *copies_info(char *name, char *value);
void set_env(char *name, char *value, list_ti *darel);
int _setenv(list_ti *darel);
int _unsetenv(list_ti *darel);

/* change.c */
void cd_parentdot(list_ti *darel);
void cdirectory_to(list_ti *darel);
void cdirectory_previous(list_ti *darel);
void cd_home_dir(list_ti *darel);

/* cd_shell_dir.c */
int cd_shell_dir(list_ti *darel);

/* builtin_cmd */
int (*builtin_cmd(char *cmd))(list_ti *darel);

/* end_shell.c */
int shell_exit(list_ti *darel);

/* ai_segment.c */
int get_length(int n);
char *conv_itst(int n);
int _stringint(char *s);

/* ai_error.c */
char *st_con(list_ti *, char *, char *, char *);
char *error_get_directory(list_ti *darel);
char *error_not_Messagefound(list_ti *darel);
char *error_exit_message(list_ti *darel);

/* ai_errorcount.c */
char *error_get_alias(char **args);
char *error_env_message(list_ti *darel);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path(list_ti *darel);


/* getc_error.c */
int getc_error(list_ti *darel, int eval);

/* get_prompt.c */
void get_prompt(int sig);

/* ai_help_env.c */
void help_enviroment(void);
void help_setenviroment(void);
void help_unsetenviroment(void);
void help_general(void);
void help_exit(void);

/* ai_help_env1.c */
void help_information(void);
void help_alias(void);
void help_cd(void);

/* get_retrivehelp.c */
int get_retrivehelp(list_ti *darel);

#endif

