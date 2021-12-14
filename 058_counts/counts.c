#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
	counts_t * count_arr = malloc(sizeof(*count_arr));
	
	count_arr->count_data = NULL;
	count_arr->count_size = 0;
	count_arr->count_unknown = 0;
	
	return count_arr;

}

void addString(counts_t * c, const char * name) {
	c->count_size++;
	c->count_data = realloc(c->count_data, c->count_size * sizeof(*c->count_data));
	c->count_data[c->count_size - 1] = malloc(sizeof(*c->count_data[c->count_size - 1]));
	c->count_data[c->count_size - 1]->string = strdup(name);
	c->count_data[c->count_size - 1]->num_str = 1;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
 	size_t temp = 1;
  	if (name != NULL){	
		for (int k = 0; k < c->count_size; k ++){
			if (strcmp(c->count_data[k]->string, name) == 0) {
				temp = 0;
				c->count_data[k]->num_str++;
				break;
			}
		}
		if (temp == 1){
			addString(c, name);
		}

	}else{
		c->count_unknown++;
	}
		

}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  	for (size_t i = 0; i < c->count_size; i++){
		fprintf(outFile, "%s: %ld\n", c->count_data[i]->string, c->count_data[i]->num_str);
	}
	if (c->count_unknown != 0 ){
		fprintf(outFile, "<unknown> : %ld\n", c->count_unknown);
	}

}

void freeCounts(counts_t * c) {
  //WRITE ME
	for (size_t k = 0; k < c->count_size; k ++) {
		free(c->count_data[k]->string);
		free(c->count_data[k]);
	}
	free(c->count_data);
	free(c);
}
