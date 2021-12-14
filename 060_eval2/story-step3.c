#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"rand_story.h"

int main(int argc, char ** argv){
	if (argc != 3){
		perror("Enter correct input argument");
		exit(EXIT_FAILURE);
	}
	FILE * f1 = fopen(argv[1], "r");
	FILE * f2 = fopen(argv[2], "r");
	if (f1 == NULL){
		perror("Open categories file fail");
		exit(EXIT_FAILURE);
	}
	
	if (f2 == NULL){
		perror("Open story file fail");
		exit(EXIT_FAILURE);
	}
	
	read_replace(f1, f2, argc);
	//readstory(f1);
	//readcategory(f2);

	if (fclose(f1) != 0){
		perror("Close categories file fail");
		exit(EXIT_FAILURE);
	}

	if (fclose(f2) != 0){
		perror("Close story file fail");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
