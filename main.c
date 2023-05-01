#include <stdio.h>

// Prototypes for the module 1 exercises
int cp();
int uname();
int cat();

int main() {
    int selection = -1;

    while (selection != 0) {
        printf("\n=== Module 1 ===\n");
        printf("Select an exercise:\n");
        printf("1. cp\n");
        printf("2. uname\n");
        printf("0. cat\n");
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                exercise1(argc[]);
                break;
            case 2:
                exercise2();
                break;
            case 3:
                exercise3();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid selection. Please try again.\n");
                break;
        }
    }
    
    return 0;
}


/*
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
            command_ex = new_sleep();
        } else if (strcmp(argv[1], "cat") == 0) {
            command_ex = new_cat();
        } else if (strcmp(argv[1], "cp") == 0) {
            command_ex = new_copy();
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
*/
