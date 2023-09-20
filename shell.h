#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <dirent.h>

extern char **environ;

#define TOK_D " \t\r\n\a\""
#define PERMISSION_DENIED 126
#define NOT_FOUND 127
#define EXIT_ERROR 2

#define ERROR -1
#define NON_INTERACTIVE_FILE 0
#define NON_INTERACTIVE_PIPED 2
#define INTERACTIVE 1

/**
 * struct list_path - singly linked list
 * @path: a string
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_path
{
	char *path;
	unsigned int len;
	struct list_path *next;
} list_path;



/*path functions*/
void free_list(list_path *head);
list_path *add_node(list_path **head, char *path);
list_path *set_all_paths_to_list();
list_path *set_all_vector_to_list();
char *check_access(char *line_av_1, list_path *current);


/*strings*/
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);

/*token*/
unsigned int _chrCheck(char c, const char *str);
char *_strtok(char *str, const char *delim);
void free_l_v(char *line, char **line_vector);
int is_dir(char *line, char **argv, int counter,
			char **line_vector, int *status, char *old_line);

/*main*/
size_t print_list(const list_path *p);
void set_list_env(list_path *p);
size_t env_list_len(const list_path *p);
void is_not_built_in(char **line_vector, char *env[], int *status,
						int counter, list_path *current, char *argv[]);
/*semicolon*/
void print_error(char *program_name, int counter,
		char *command, int type_of_error);
void print_cant_open(char *program_name, int counter, char *file_name);


char **text_to_vector(char *text);
char **file_non_interactive(char *file_name, char *program_name);
char **piped_non_interactive();
char **get_commands(int mode, char *file_name, char *program_name);

int _atoi(char *s);
void is_exit(char *line, char **line_vector, list_path *current,
		char *program_name, int counter, int *status, list_path *env, char **lines);


/*comments*/
void handle_comments(char *input);
int _cd(char *line_vector[], char **argv);
void free_all(char **lines, int counter, list_path *env,
				list_path *current, char *line, char **line_vector);

/*getline*/
ssize_t _getlineHelper(char **lineptr, size_t *n,
		__attribute__((unused)) FILE * stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/*helper functions*/
int _varcmp(char *var_name, char *full_var);
list_path *get_variable(char *name, list_path *head);
char *num_to_char(int num);
char **get_av_with_flags(char *line, int status);
unsigned int char_count_piped(char *str, char c);
char *_getenv(char *name);
unsigned int char_count(char *str, char c);


void handle_semicolons(char *line);
void execute_command_with_waitpid(char *path, char **av, char **env);
void execute_command(char *path, char **av, char **env, int *status);

/*builtins*/
void print_env(int *status);
char *get_status(int n);
char *get_process_id();
int is_built_in(char *line, char **line_vector, list_path *current,
		char *program_name,
		int counter, int *status, list_path *env, char **lines, char **argv);
void _setenv(char *name, char *value, list_path *env_list);



char *get_command_from_user(list_path *current);
char *get_command_from_file(char *file);
void free_vector(char **v);
int check_mode(int argc);


#endif
