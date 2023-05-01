#include <stdio.h>
#include <stdlib.h>

// Prototypes for the module 1 exercises
int copy(int argc, char *argv[]);
int uname_command(char *arg_list[]);
int cat();

int main(int argc, char *argv[]) {
    int selection = -1;

    while (selection != 0) {
        printf("\n=== Module 1 ===\n");
        printf("Select an exercise:\n");
        printf("1. copy\n");
        printf("2. uname\n");
        printf("3. cat\n");
        printf("0. Exit\n");
        scanf("%d", &selection);

        (selection > 0) ? int failure = 0 : 0;

        switch (selection) {
            case 1:
                failure = copy(int argc, char *argv[]);
                if (failure){
                    printf("Copy command failed");
                    exit(1);
                }
                break;
            case 2:
                failure = uname_command(char *argv[]);
                if (failure){
                    printf("uname command failed");
                    exit(1);
                }
                break;
            case 3:
                failure = cat();
                if (failure){
                    printf("cat command failed");
                    exit(1);
                }
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