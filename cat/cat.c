#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cat(){

    char str1[4096];
    printf("\nPlease enter the name or path and name of a file to be read by cat\n");
    scanf("%4095s", str1);
    printf("\n");
    FILE *fp;
    char buffer[4096];

        fp = fopen(str1,"rb");
        printf("======================================================\n");
        while (fgets(buffer, 4096, fp))
        {
            buffer[strlen(buffer) - 1] = '\0';            
            fprintf(stdout,"%s\n",buffer);            
        }
        printf("======================================================\n");

    return 0;
}
