#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int fileBrowser(const char *argv[]){

	int i=0;
	char dirname[100];

	DIR *dp;
	struct dirent *dir;

	struct stat statbuf;

	if(stat(argv[1],&statbuf) != -1){
		switch(statbuf.st_mode & S_IFMT){
			case S_IFDIR:
				printf("Normal DIR\n");
				strcat(dirname,argv[1]);
				break;
			case S_IFREG:
				printf("Is regular file\n");
				strcat(dirname,argv[1]);

				for(int i=strlen(dirname)-1;i>0;i--){
					if(dirname[i] == '/')
						break;
					dirname[i]='\0';
				}
				break;
			default:
				break;
		}
	}
	else{
		printf("File doesn't exist :( \n");
		exit(1);
	}
	getchar();

	if((dp=opendir(dirname)) == NULL){
		printf("can't open directory: %s",dirname);
		exit(0);
	}

	while((dir=readdir(dp)) != NULL){
		printf("\t%s\n", dir->d_name);
	}

	closedir(dp);
	return 0;
}
