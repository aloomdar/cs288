#include <stdio.h>

void hexPrint(unsigned char* arg){
	for(int i = 7; i >= 0; i--){
		printf("%02hhx ", *arg+i);
	}
}

int main(int argc, char* argv[])
{
	unsigned char *p = (unsigned char *) &argv;
	printf("Argument count: %d\n", argc);
	printf("argv \t| %p \t| %p\n\n", p, p);
	for(int i = 0; i < argc; i++){
		printf("argv[%d] | ", i);
		unsigned char* p2 = (unsigned char *) argv[i];
		for(int j = 7; j >= 0; j--){
			printf("%02hhx ", *(p2 + j));
		}
		printf("| %p\n", &p+i);
	}
	return 0;
}

