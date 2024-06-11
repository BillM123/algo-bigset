#include <stdio.h>
#include "dependencies/include/datatypes.h"
#include "dependencies/include/prototypes.h"
#define NUUM 100


int main(){
    struct pairs arr[NUUM] = {{0}, {0}, {0}};

    for(int i = 0; i < NUUM; i++){
        arr[i].numOfsps = i;
        arr[i].i = i;
        arr[i].j = i+1;
    }

    sort(arr, NUUM);

     for (int i = 0; i < NUUM; i++) {
        printf("%d: %d (%d<-->%d)\n", i, arr[i].numOfsps, arr[i].i, arr[i].j);
    }

    return 0;
}