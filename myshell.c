#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

#define MAX_LINE_LENGTH 2000
#define MAX_ARGUMENTS 10
#define TRUE 1

#define DEFAULT 0
#define EXIT 1
#define CD 2

void getUserInfo(char* buf) {
    printf("myShell> ");
    if (fgets(buf, MAX_LINE_LENGTH, stdin) == NULL) {
        printf("An error occurred reading input. Please try again.\n");
    }
}

void parseInput(char** args, char* input) {
    int i = 0;
    while (i < MAX_ARGUMENTS - 1) {
        char* token = strsep(&input, " \n");
        if (token == NULL)
            break;
        if (*token == '\0')
            continue;

        args[i++] = token;
    }
    args[i] = NULL;
}

int argToNumber(const char* command) {
    if (strcmp(command, "exit") == 0)
        return EXIT;
    else if (strcmp(command, "cd") == 0)
        return CD;
    return DEFAULT;
}

int isBackgroundProcess(char** args) {
    if (args == NULL || args[0] == NULL) return 0;
    int i = 0;
    while (args[i + 1] != NULL) {
        i++;
    }
    if (strcmp(args[i], "&") == 0) {
        args[i] = NULL;
        return 1;
    }
    return 0;
}

int runShell() {
    char* userInput = malloc(MAX_LINE_LENGTH * sizeof(char));
    char** args = malloc(MAX_ARGUMENTS * sizeof(char*));

    while (TRUE) {
        getUserInfo(userInput);
        parseInput(args, userInput);
        if (args[0] == NULL)
            continue;
        switch (argToNumber(args[0])) {
            case EXIT:
                free(userInput);
                free(args);
                return 0;
            case CD:
                if (chdir(args[1] == NULL ? getenv("HOME") : args[1]) != 0)
                    perror("cd error");
                break;
            default: {
                int background = isBackgroundProcess(args);
                pid_t pid = fork();
                if (pid == 0) {
                    execvp(args[0], args);
                    perror("exec error");
                    exit(1);
                } else {
                    if (!background) {
                        int exit_signal;
                        waitpid(pid, &exit_signal, 0);
                    }
                }
            } break;
        }
    }
}

int main() {
    runShell();
}
