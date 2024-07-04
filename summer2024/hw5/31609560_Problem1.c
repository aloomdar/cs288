#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
	
	char str[2000] = "";
	
	for(int i = 0; i < argc; i++){
		strcat(strcat(str, " "), argv[i]);		
	}
	
	for(int i = 0; i < strlen(str); i++){
		if(isprint(str[i])){
			if(str[i] == ' '){
				printf("%02hhx", str[i]);
				printf("\(\\");
				printf("0) ");
			}
			else{
				printf("%02hhx(%c) ", str[i], str[i]);
			}
		}
	}
	printf("\n");
	return 0;
}

