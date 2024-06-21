#include <stdio.h>
#include <string.h>
#include <dirent.h>

int countLines(const char *pathname){
	DIR* dir = opendir(pathname);
	if (dir == NULL) {
		return -1;
	}
	int count = 0;
	struct dirent *entity;
	while ((entity = readdir(dir)) != NULL){
		if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0){
			char path [100] = { 0 };
			strcat(path, pathname);
			strcat(path, "/");
			strcat(path, entity->d_name);
			count = count + countLines(path);
		}	
		else if (entity->d_type == DT_REG){
			char path [100] = { 0 };
                        strcat(path, pathname);
                        strcat(path, "/");
                        strcat(path, entity->d_name);
			FILE *f;
			f = fopen(path, "r");
			for (char c = getc(f); c != EOF; c = getc(f)){
				if (c == '\n'){
					count = count + 1;
				}				
			}
			fclose(f);
		}
	}
	closedir(dir);
	return count;
}

int main(){
	char pathname[1000];
	printf("Enter a directory:\n");
	scanf("%s", pathname);

	int answer = countLines(pathname);
	if(answer == -1){
		printf("Cannot find directory.\n");
	}
	else{
		printf("The total number of lines: %d\n", answer);
	}
	return 0;
}
