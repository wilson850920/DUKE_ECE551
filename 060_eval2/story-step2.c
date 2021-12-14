#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"rand_story.h"

int main(int argc, char ** argv){
	if (argc != 2){
		perror("Enter correct input argument");
		exit(EXIT_FAILURE);
	}
	FILE * f = fopen(argv[1], "r");
	if (f == NULL){
		perror("Open file fail");
		exit(EXIT_FAILURE);
	}
	
	readcategory(f);
		
	//catarray_t * cate = createCat();
	//ssize_t len = 0;
	//size_t sz = 0;
	//char * line = NULL;
	//
	//while ((len = getline(&line, &sz, f)) >= 0){
	//	cate = getCate(line, cate);
	//}
	//
	//printWords(cate);
	//freecat(cate);
	//free(line);
	if (fclose(f) != 0){
		perror("Close file fail");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
