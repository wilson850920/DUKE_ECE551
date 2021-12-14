#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvpair_t * findpair(const char * line, char split_symbol){
	const char * p = line;
	const char * x = line;

	p = strchr(p, split_symbol);
	x = strchr(line, '\n');
	
	if ((p == NULL) || (x == NULL)){
		fprintf(stderr, "The line doesn't contain a split symbol");
		exit(EXIT_FAILURE);
	}
	
	kvpair_t * newpair = malloc(sizeof(*newpair));

	size_t key_len = p - line + 1;
	newpair->key = malloc(key_len * sizeof(*newpair->key));
	strncpy(newpair->key, line, key_len - 1);
	newpair->key[key_len - 1] = '\0';

	size_t val_len = x - p;
	newpair->value = malloc(val_len * sizeof(*newpair->value));
	strncpy(newpair->value, p + 1, val_len - 1);
	newpair->value[val_len - 1] = '\0';
	
	return newpair;
}

void getpair(const char * line, kvarray_t * key_value){
	
	kvpair_t * pairing = NULL;
	pairing = findpair(line, '=');
	
	key_value->kv_data = realloc(key_value->kv_data, (key_value->n_pair + 1) * sizeof(*key_value->kv_data));
	key_value->kv_data[key_value->n_pair] = pairing;
	key_value->n_pair++;

	pairing = NULL;

}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
	FILE * f = fopen(fname, "r");
	if (f == NULL){
		fprintf(stderr, "could not open file");
		return NULL;
	}

	char * line = NULL;
	size_t sz = 0;
	ssize_t len =0;

	kvarray_t * key_value = malloc(sizeof(*key_value));
	key_value->kv_data = NULL;
	key_value->n_pair = 0;

	while ((len = getline(&line, &sz, f)) >= 0){
		getpair(line, key_value);
	}
	free(line);

	if (fclose(f) != 0 ){
		fprintf(stderr, "failed to close the input file!");
		return NULL;
	}
	return key_value;
}



void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  
	for (int i = 0; i < pairs->n_pair; i++){
		free(pairs->kv_data[i]->key);
		free(pairs->kv_data[i]->value);
		free(pairs->kv_data[i]);
	}
	free(pairs->kv_data);
	free(pairs);

}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  	
	for (size_t i = 0; i < pairs->n_pair; i ++){
		printf("key = '%s' value = '%s'\n", pairs->kv_data[i]->key, pairs->kv_data[i]->value);
	}
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME

	for (size_t i = 0; i < pairs->n_pair; i ++){
		if (strcmp(pairs->kv_data[i]->key, key) == 0) {
			return pairs->kv_data[i]->value;
		}
	}
	return NULL;
}
