#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cat(int a, char **v){

    FILE *fp;
    char buffer[4096];

    if(a > 1){
        fp = fopen(v[a - 1],"rb");

        while (fgets(buffer, 4096, fp))
        {
            buffer[strlen(buffer) - 1] = '\0';
            fprintf(stdout,"%s\n",buffer);
        }
        

    }else{
        printf("Enter a file as a second argument\n");
    }
    return 0;
}