#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  	const char * add = ".counts";
	unsigned len = strlen(inputName) + strlen(add) + 1;
	
	char * total_len = malloc(len * sizeof(*total_len));
	strcpy(total_len, inputName);
	strcat(total_len, add);
	return total_len;
	
}
