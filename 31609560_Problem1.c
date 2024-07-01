#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

    printf("argv \t %p \t %p", &argv[0], &argv[0]);
    return 0;
    
}