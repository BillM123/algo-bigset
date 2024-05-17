#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 512
#define FORMAT1 "%d,%d\n"
#define FORMAT2 "%d %d\n"

int getFormat(FILE *file, int *isIndex){
    char *buf = NULL;
    size_t num, n;
    int num1 = 0, num2 = 0;
    
    getline(&buf, &n, file);
    num = atoi(buf);
    if(num != 0){
        (*isIndex)++;
    }

    fscanf(file, FORMAT1, &num1, &num2);
    if(num1 != 0 && num2 != 0){
        free(buf);
        return 1;
    }
    fscanf(file, FORMAT2, &num1, &num2);
    if(num1 != 0 && num2 != 0){
        free(buf);
        return 2;
    }

    free(buf);
    return -1;
}

int main(int argc, char *argv[]){
    if(argv[1] == NULL){
        printf("No input provided, exiting...\n");
        return 1;
    }
    if(argv[2] == NULL){
        printf("No location to write out provided, exiting...\n");
        return 1;
    }
    FILE *fileIn = fopen(argv[1], "r");
    if (fileIn == NULL) {
        printf("Error opening file. Input might be invalid\n");
        return 1;
    }
    FILE *fileOut = fopen(argv[2], "w");
    if(fileOut == NULL){
        printf("Output already exists, skipping...\n");
    }

    int isIndex = 0;
    int num1 = 0, num2 = 0;
    int format = getFormat(fileIn, &isIndex);
    int vertnum;

    fseek(fileIn, 0L, SEEK_SET);

    if(isIndex == 1){
        char *buf = NULL;
        size_t n;

        getline(&buf, &n, fileIn);
        fprintf(fileOut, "%s", buf);
        vertnum = atoi(buf);
        free(buf);
    }
    else{
        if(argv[3] == NULL){
            printf("Number of vertices exists neither in input file nor in arg 3, exiting...\n");
            return 1;
        }
        fprintf(fileOut, "%s", argv[3]);
        vertnum = atoi(argv[3]);
    }
    int **array = malloc((vertnum)*sizeof(int*));
    for(int i = 0; i < vertnum; i++){
        array[i] = malloc((vertnum)*sizeof(int));
        for(int j = 0; j < vertnum; j++){
            //array[i][j] = malloc(sizeof(int));
            array[i][j] = 0;
        }
    }

    if(format == 1){
        while(fscanf(fileIn, FORMAT1, &num1, &num2)){
            array[num1-1][num2-1] = 1; 
            if(array[num2-1][num1-1] != 1){
                fprintf(fileOut, "%d %d\n", num1, num2);
            }
        }
    }
    else if(format == 2){
        while(fscanf(fileIn, FORMAT2, &num1, &num2)){
            array[num1-1][num2-1] = 1; 
            if(array[num2-1][num1-1] != 1){
                fprintf(fileOut, "%d %d\n", num1, num2);
            }
        }
    }
    fprintf(fileOut, "end\n");    
    return 0;
} 
