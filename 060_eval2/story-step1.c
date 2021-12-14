#include<stdio.h>
#include<stdlib.h>
#include"rand_story.h"
#include<string.h>

int main(int argc, char ** argv) {

	if (argc != 2) {
		perror("Enter correct input argument");
		exit(EXIT_FAILURE);
	}
	FILE * f = fopen(argv[1], "r");
	if (f == NULL) {
		perror("Open file fail");
		exit(EXIT_FAILURE);
	}

	readstory(f);
	
	//size_t sz = 0;
	//ssize_t len = 0;
	//char * line = NULL;
	//char * out_arr = NULL; //= malloc(sizeof(*out_arr));
	//while ((len = getline(&line, &sz, f)) >= 0) {
	//	//if (line == NULL){
	//	//	perror("Found nothing in the file");
	//	//	exit(EXIT_FAILURE);
	//	//}
	//	testing(line, len);	
	//}
	////if ((fgetc(f)) == EOF){
	////	perror("Nothing to read");
	////	exit(EXIT_FAILURE);
	////}
	//free(out_arr);
	//free(line);
	
	if (fclose(f) != 0) {
		perror("Close file fail");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
