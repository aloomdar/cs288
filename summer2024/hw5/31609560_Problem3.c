#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char **a, char **b){
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(char *arr[], int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size -i -1; j++){
            char *a = *(&arr[j]);
            char *b = *(&arr[j+1]);
            if(strcmp(a, b) > 0){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main(int argc, char **argv, char *envp[]){

    int index = 0;
    while(envp[index]){
        index++;
    }

    bubblesort(envp, index);
    for(int i = 0; i < index; i++){
        printf("%s\n", envp[i]);
    }
}
