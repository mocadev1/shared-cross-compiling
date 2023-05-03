#include <stdio.h>
#include <stdlib.h>
#include "copy/copy.h"
#include "uname/uname.h"
#include "cat/cat.h"


// Prototypes for the module 1 exercises
int copy();
int uname_command(char *arg_list[]);
int cat(void);

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

        int failure = 0;

        switch (selection) {
            case 1:
                failure = copy();
                if (failure){
                    printf("Copy command failed");
                    exit(1);
                }
                break;
            case 2:
                failure = uname_command(argv);
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
// Dummy funcs
    // int copy(int argc, char *argv[]){
    //     printf("copy function called\n");
    //     return 0;
    // }

    // int uname_command(char *arg_list[]){
    //     printf("uname_command function called\n");
    //     return 0;
    // }

    // int cat(){
    //     printf("cat function called\n");
    //     return 0;
    // }
    
    return 0;
}