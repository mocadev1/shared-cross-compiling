#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    // printf("Got %s...",argv[1]);
    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Check if this is the child process
        char *command_ex = NULL;

        if (strcmp(argv[1], "sleep") == 0) {
            command_ex = "./alex_sleep";
        } else if (strcmp(argv[1], "uname") == 0) {
            command_ex = "./alex_uname";
        } else if (strcmp(argv[1], "ls") == 0) {
            command_ex = "./alex_ls";
        } else if (strcmp(argv[1], "cat") == 0) {
            command_ex = "./alex_cat";
        } else if (strcmp(argv[1], "lsmod") == 0) {
            command_ex = "./alex_lsmod";
        } else if (strcmp(argv[1], "uptime") == 0) {
            command_ex = "./alex_uptime";
        } else if (strcmp(argv[1], "chmod") == 0) {
            command_ex = "./alex_chmod";
        } else if (strcmp(argv[1], "cp") == 0) {
            command_ex = "./alex_copy";
        } else {
            fprintf(stderr, "Unknown command: %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        char *args[] = {command_ex, argv[2], argv[3], argv[4], argv[5], NULL}; // Setup the arguments to be executed

        execvp(args[0], args); // Execute the command with arguments

        // If execvp returns, an error has occurred
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // This is the parent process
        // Wait for the child process to finish
        waitpid(pid, &status, 0);

        // Check if the child process exited normally
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }

    return 0;
}