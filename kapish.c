#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <errno.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "doublylinkedlist.h"

#define MAXCHAR 512

extern char **environ;

void (*origin_handler)(int) = NULL;
void my_handler(int signal);

int parse_command_line(char *command_line);
char **init_commands(int num);
void get_commands(const char *command_line, char **commands, int num);
void free_commands(char **commands);

bool end_with(const char *str, const char *suffix);

void cd(const char *dir);
void history();
void run_history(const char *command_prefix);
void set_env();
void un_set_env();
void execute_external(char * const commands[]);

void process_lines(FILE *fp, bool print_prompt, bool insert_history);
void process_line(char *line);

dlist *list;

int main()
{
    origin_handler = signal(SIGINT, my_handler);

    list = create_dlist();

    char *home = getenv("HOME");
    char *file = malloc(sizeof(char) * strlen(home) + sizeof(".kapishrc") + 2);
    sprintf(file, "%s/.kapishrc", home);

    FILE *fp = fopen(file, "r");
    if (fp)
    {
        process_lines(fp, false, true);
        fclose(fp);
    }

    free(file);

    process_lines(stdin, true, true);

    free_dlist(list);
    return EXIT_SUCCESS;
}

void my_handler(int signal) {
    switch (signal) {
        case SIGINT:
            printf("\n");
            return;
        default:
            origin_handler(signal);
    }
}

void process_lines(FILE *fp, bool print_prompt, bool insert_history)
{
    if (print_prompt)
        printf("? ");

    char line[MAXCHAR];
    while (fgets(line, MAXCHAR, fp) != NULL)
    {
        if (!print_prompt)
            printf("? %s", line);

        if (end_with(line, "\n"))
            line[strlen(line) - 1] = 0;

        if ('!' == line[0])
        {
            run_history(line + 1);
        }
        else
        {
            if (insert_history)
                push_front(list, line);

            process_line(line);
        }

        if (print_prompt)
            printf("? ");
    }
}

void process_line(char *line)
{
    int token_num = parse_command_line(line);
    if (!token_num)
        return;

    char **commands = init_commands(token_num);
    get_commands(line, commands, token_num);

    if (0 == strcmp("setenv", commands[0]))
    {
        if (2 == token_num)
            set_env(commands[1], "");
        else if (3 == token_num)
            set_env(commands[1], commands[2]);
    }
    else if (0 == strcmp("unsetenv", commands[0]))
    {
        if (2 == token_num)
            un_set_env(commands[1]);
    }
    else if (0 == strcmp("cd", commands[0]))
    {
        if (1 == token_num)
            cd(getenv("HOME"));
        else if (2 == token_num)
            cd(commands[1]);
    }
    else if (0 == strcmp("history", commands[0]))
    {
        if (1 == token_num)
            history();
    }
    else if (0 == strcmp("exit", commands[0]))
    {
        free_dlist(list);
        _exit(EXIT_SUCCESS);
    }
    else
    {
        execute_external(commands);
    }

    free_commands(commands);
}

void set_env(const char *var, const char *value)
{
    if (0 != setenv(var, value, true))
        fprintf(stderr, "%s\n", strerror(errno));
}

void un_set_env(const char *var)
{
    if (0 != unsetenv(var))
        fprintf(stderr, "%s\n", strerror(errno));
}

void cd(const char *dir)
{
    if (0 == chdir(dir))
    {
        char *pwd = get_current_dir_name();
        setenv("PWD", pwd, true);
        free(pwd);
    }
    else
    {
        fprintf(stderr, "%s\n", strerror(errno));
    }
}

void history()
{
    rprint(list);
}

void run_history(const char *command_prefix)
{
    node *node = ffind(list, command_prefix);
    if (node)
    {
        char *buf = malloc(strlen(value(node)) + 1);
        strcpy(buf, value(node));
        process_line(buf);
        free(buf);
    }
    else
    {
        fprintf(stderr, "Can not find the command in history list.\n");
    }
}

void execute_external(char * const commands[])
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        free_dlist(list);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (-1 == execvp(commands[0], commands))
        {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(EXIT_FAILURE);
        }
        else
        {
            _exit(EXIT_SUCCESS);
        }
    }
    else
    {
        int status;
        (void)waitpid(pid, &status, 0);
    }
}

int parse_command_line(char *command_line)
{
    int ret = 0;
    char *pch = strtok(command_line, " \t");
    while (NULL != pch)
    {
        ret++;
        pch = strtok(NULL, " \t");
    }
    return ret;
}

char **init_commands(int num)
{
    return malloc(sizeof(char *) * (num + 1));
}

void get_commands(const char *command_line, char **commands, int num)
{
    while (num-- > 0)
    {
        *commands++ = strtok((char *)command_line, " \t");
        command_line += strlen(command_line) + 1;
    }
    *commands = 0;
}

void free_commands(char **commands)
{
    free(commands);
}

bool end_with(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return false;

    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr)
        return false;

    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}
