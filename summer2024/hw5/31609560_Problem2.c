#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int opt;
	while((opt = getopt(argc, argv, ":cdf:us:")) != -1){
		switch(opt){
		case 'c':
		case 'd':
		case 'u':
			printf("Option: %c\n", opt);
			break;
		case 'f':
			printf("Field: %s\n", optarg);
			break;
		case 's':
			printf("Char: %s\n", optarg);
			break;
		case ':':
			printf("Option %c needs a value\n", optopt);
			break;
		case '?':
			printf("Unknown option: %c\n", optopt);
			break;
		}
	}
	for(; optind < argc; optind++){
		printf("Argument: %s\n", argv[optind]);
	}
	exit(0);
}
