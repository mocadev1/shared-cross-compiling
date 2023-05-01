#include <stdio.h>
#include "./inc/cat.h"
// Prototypes for the module 1 exercises
//int cp();
//int uname();
//int cat();

int main() {
    int selection = -1;

    while (selection != 0) {
        printf("\n=== Module 1 ===\n");
        printf("Select an exercise:\n");
        printf("1. cp\n");
        printf("2. uname\n");
        printf("3. cat\n");
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                //exercise1(argc[]);
                break;
            case 2:
                //exercise2();
                break;
            case 3:
                cat();
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

