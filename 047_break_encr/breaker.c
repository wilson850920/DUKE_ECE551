#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char b_encrypt(FILE *f){
	int c;
	int b;
	int array[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int max = array[0];
	int element;
	while ((c = fgetc(f)) != EOF) {
		if (isalpha(c)) {
			c = tolower(c);
			b = c - 97;		
			array[b] ++;
		//printf("%c\n", c);
		//printf("b = %d\n", b);

		}else{
			continue;
		}
	}
	for (int i = 0; i < 25; i++) {
		if (array[i] > max) {
			max = array[i];
			element = i;
		}
	//for (int i = 0;i < 26; i++) {
	//	printf("%d\n",array[i]);
	//}
	}
	//printf("i = %d\t, max element is %d\n",element ,max);
	char freq = 'a' + element;
	//printf("%d\n", freq);
	int key = (26 + freq - 'e') % 26;
	if (key < 0 || key >= 26) {
		return EXIT_FAILURE;
	}

	return key;
}


int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: encrpyt key input FileName\n");
		return EXIT_FAILURE;
	}

	FILE * f = fopen(argv[1], "r");
	if (f == NULL) { 
		perror("Cpuld not open file");
		return EXIT_FAILURE;
	}
	int max_freq = b_encrypt(f);
	//b_encrypt(f);
	printf("%d\n", max_freq);
	if  (fclose(f) != 0) { 
		perror("Failed to clse the input file!");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
