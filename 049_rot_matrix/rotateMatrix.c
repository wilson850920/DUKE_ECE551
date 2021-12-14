#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void rotateMatrix(FILE *f){
	//int c;
	char matrix[10][10] = {{0}};
	char line[12] = {0};
	
	for (int k = 0; k < 10; k++){
		if (fgets(line, 12, f) != NULL) {
			if (strchr(line, '\n') == NULL){
				fprintf(stderr, "Line character exceeds 10.");
				exit(EXIT_FAILURE);
			}
			if(line[0] == '\n'){
				fprintf(stderr, "There are less than 10 lines");
				exit(EXIT_FAILURE);
			}
		       	if(line[10] != '\n'){
				fprintf(stderr, "Thereis a line without 10 character");
				exit(EXIT_FAILURE);
			}else {
				for (int i = 0; i < 10; i ++){
					if (line[i] == '\n'){
						fprintf(stderr, "There is a line which have less than 10 character");
						exit(EXIT_FAILURE);
					}else{
						matrix[i][9 - k] = line[i];
					}
				}
			}
		}else{
			fprintf(stderr, "There are less then 10 lines");
			exit(EXIT_FAILURE);
		}
	}
	
	if (fgets(line, 12, f) != NULL) {
		fprintf(stderr, "There are more than ten lines\n");
		exit(EXIT_FAILURE);
	}


	//printf("%s\n", *matrix);
	for (int i = 0; i < 10; i ++){
		for (int l = 0; l < 10; l ++){
			printf("%c", matrix[i][l]);
		}
		printf("%c", '\n');	
	
	}
	//printf("%s", matrix);	
}


int main (int argc, char ** argv){
	if (argc != 2){
		fprintf(stderr, "Usage: encrypt key inputFileName\n");
		return EXIT_FAILURE;
	}
	FILE * f = fopen(argv[1], "r");
	if (f == NULL){
		perror("Could not open file");
		return EXIT_FAILURE;
	}
	rotateMatrix(f);
	if (fclose(f) != 0){
		perror("Failed to close the input file!");
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}
