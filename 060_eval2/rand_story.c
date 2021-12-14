#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialize Catarray_t 
catarray_t * createCat(void) {
  catarray_t * cat_arr = malloc(sizeof(*cat_arr));
  cat_arr->arr = NULL;
  cat_arr->n = 0;
  return cat_arr;
}

//Initialize Category_t
category_t * createCate(void) {
  category_t * cate_arr = malloc(sizeof(*cate_arr));
  cate_arr->name = NULL;
  cate_arr->words = NULL;
  cate_arr->n_words = 0;
  return cate_arr;
}

//split the input line and grep the category
char * split_line_cat(const char * line, char split_sym) {
  const char * p = line;
  p = strchr(line, split_sym);
  if (p == NULL) {
    fprintf(stderr, "The line doesn't contain a split symbol");
    exit(EXIT_FAILURE);
  }
  size_t cat_len = p - line + 1;
  if (cat_len == 1){
	  perror("Category empty, Warning");
	  exit(EXIT_FAILURE);
  }
  char * cat = malloc(cat_len * sizeof(*cat));
  strncpy(cat, line, cat_len - 1);
  cat[cat_len - 1] = '\0';
  return cat;
}

//split the input line and grep the word
char * split_line_word(const char * line, char split_sym) {
  const char * p = line;
  const char * x = line;
  p = strchr(line, split_sym);
  x = strchr(line, '\n');
  if (x == NULL) {
    fprintf(stderr, "The line doesn't contain a next line symbol");
    exit(EXIT_FAILURE);
  }
  size_t word_len = x - p;
  char * word = malloc(word_len * sizeof(*word));
  strncpy(word, p + 1, word_len - 1);
  word[word_len - 1] = '\0';
  return word;
}

//add the category into Catarray when it's not in the category list
catarray_t * addCat(catarray_t * cate, char * cat, char * word) {
  size_t temp = 1;
  size_t index;
  if (cat != NULL && word != NULL) {
    for (size_t i = 0; i < cate->n; i++) {
      if (!strcmp(cat, cate->arr[i].name)) {
        temp = 0;
        index = i;
        break;
      }
    }
    if (temp == 1) {  //The current catarray doesn't contain the input category
      cate->n++;
      cate->arr = realloc(cate->arr, cate->n * sizeof(*cate->arr));
      cate->arr[cate->n - 1].n_words = 0;
      cate->arr[cate->n - 1].words = NULL;
      cate->arr[cate->n - 1].name = cat;
      cate->arr[cate->n - 1].n_words++;
      cate->arr[cate->n - 1].words =
          realloc(cate->arr[cate->n - 1].words,
                  cate->arr[cate->n - 1].n_words * sizeof(*cate->arr[cate->n - 1].words));
      cate->arr[cate->n - 1].words[cate->arr[cate->n - 1].n_words - 1] = word;
    }
    else {
      cate->arr[index].n_words++;
      cate->arr[index].words =
          realloc(cate->arr[index].words,
                  cate->arr[index].n_words * sizeof(*cate->arr[index].words));
      cate->arr[index].words[cate->arr[index].n_words - 1] = word;
      free(cat);
    }
  }
  if (cat == NULL) {
    perror("Category missing");
    exit(EXIT_FAILURE);
  }
  if (word == NULL) {
    perror("Word missing");
    exit(EXIT_FAILURE);
  }
  return cate;
}

//split the input line and add into Catarray
catarray_t * getCate(const char * line, catarray_t * cate) {
  char * cat = split_line_cat(line, ':');
  char * word = split_line_word(line, ':');
  cate = addCat(cate, cat, word);
  return cate;
}

//free the catarray part
void freecat(catarray_t * cate) {
  for (size_t j = 0; j < cate->n; j++) {
    for (size_t h = 0; h < cate->arr[j].n_words; h++) {
      free(cate->arr[j].words[h]);
    }
    free(cate->arr[j].words);
    free(cate->arr[j].name);
  }
  free(cate->arr);
  free(cate);
}

//print the output for part one
void organize(ssize_t * rep_arr, int numrep, const char * line, ssize_t len) {
  for (int k = 0; k < numrep; k++) {
    if (k == 0) {
      for (ssize_t i = 0; i < rep_arr[k]; i++) {
        printf("%c", line[i]);
      }
    }
    else if ((k % 2 == 0) && k != 0) {
      for (ssize_t i = rep_arr[k - 1] + 1; i < rep_arr[k]; i++) {
        printf("%c", line[i]);
      }
    }
    else if (k % 2 == 1) {
      printf("%s", chooseWord("verb", NULL));
    }

    if ((k == numrep - 1) && (rep_arr[k] != len)) {
      for (ssize_t i = rep_arr[k] + 1; i < len; i++) {
        printf("%c", line[i]);
      }
    }
  }
}

//check the replacement for the given symbol
ssize_t * checkrep(const char * line, ssize_t len, ssize_t * rep_arr) {
  int numrep = 0;
  for (ssize_t i = 0; i < len; i++) {
    if (line[i] == '_') {
      numrep++;
      rep_arr = realloc(rep_arr, numrep * sizeof(*rep_arr));
      rep_arr[numrep - 1] = i;
    }
  }
  if (numrep % 2 == 1) {
    perror("The Number of the replace symbol must be an even number");
    exit(EXIT_FAILURE);
  }

  organize(rep_arr, numrep, line, len);

  return rep_arr;
}

//prepare the category index list
void replace(const char * line, ssize_t len) {
  ssize_t * rep_arr = NULL;
  rep_arr = checkrep(line, len, rep_arr);
  free(rep_arr);
}

//For step four, unfortunately I didn't made it work :(
const char * repeatword(char * w, catarray_t * cat, const char * b){
	for (size_t i = 0; i < cat->n; i++){
		if (strcmp(w, cat->arr[i].name) == 0){
			for (size_t j = 0; j < cat->arr[i].n_words; j ++){
				if (strcmp(b, cat->arr[i].words[j]) == 0){
					return chooseWord(w, cat);
				}
				else{
					return b;
				}
			}
		}
	}
	return b;
}

//print the category result for step 3 and 4 
void determine(category_t * hist, catarray_t * cat, char * w, size_t length, int argc) {
  long ret;
  char * ptr;
  ret = strtol(w, &ptr, 10);

  if (ptr == w) {
    if (argc == 3){
      const char * a = chooseWord(w, cat);
      hist->words[hist->n_words] = malloc((strlen(a)+1) * sizeof(*hist->words[hist->n_words]));
      strcpy(hist->words[hist->n_words], a);
      printf("%s", hist->words[hist->n_words]);
    }
    else{ // argc = 4
      const char * b = chooseWord(w, cat);
      
      for (size_t i = 0; i < cat->n; i++){
	      if (strcmp(w, cat->arr[i].name) == 0){
		      for (size_t j = 0; j < cat->arr[i].n_words; j ++){
			      if (strcmp(b, cat->arr[i].words[j]) == 0){
				      b = chooseWord(w, cat);
				}
		      }
	      }
      }
      hist->words[hist->n_words] = malloc((strlen(b)+1) * sizeof(*hist->words[hist->n_words]));
      strcpy(hist->words[hist->n_words], b);
      printf("%s", hist->words[hist->n_words]);
    }
  }else{
	  if (ret > hist->n_words || ret < 1){
		  perror("List out if range");
		  exit(EXIT_FAILURE);
	  }
    hist->words[hist->n_words] = malloc((strlen(hist->words[hist->n_words - ret])+1) * sizeof(*hist->words[hist->n_words]));
    strcpy(hist->words[hist->n_words], hist->words[hist->n_words - ret]);
    printf("%s", hist->words[hist->n_words]);
    
  }

}

//print out the line where that are not categories 
category_t * store_cate(ssize_t * temp_arr,
                        int num,
                        const char * line,
                        ssize_t len,
                        category_t * hist,
                        catarray_t * cat,
			int argc) {
  for (int k = 0; k < num; k++) {
    if (k == 0) {
      for (ssize_t i = 0; i < temp_arr[k]; i++) {
        printf("%c", line[i]);
      }
    }
    else if ((k % 2 == 0) && k != 0) {
      for (ssize_t i = temp_arr[k - 1] + 1; i < temp_arr[k]; i++) {
        printf("%c", line[i]);
      }
    }
    else if ((k % 2) == 1) {
      const char * p = line;
      size_t length = temp_arr[k] - temp_arr[k - 1];
      char * w = malloc((length + 1) * sizeof(*w));
      hist->words = realloc(hist->words, (hist->n_words + 1) * sizeof(*hist->words));
      p = &line[temp_arr[k - 1] + 1];
      w = strncpy(w, p, length);
      w[length - 1] = '\0';
      determine(hist, cat, w, length, argc);
      hist->n_words++;
      free(w);
    }
    if ((k == num - 1) && (temp_arr[k] != len)) {
      for (ssize_t i = temp_arr[k] + 1; i < len; i++) {
        printf("%c", line[i]);
      }
    }
  }
  return hist;
}

//calculate how much replace symbol has been placed
category_t * wait_for_replace(const char * line,
                              ssize_t len,
                              category_t * hist,
                              catarray_t * cat,
			      int argc) {
  ssize_t * temp_arr = NULL;
  int num = 0;
  for (ssize_t i = 0; i < len; i++) {
    if (line[i] == '_') {
      num++;
      temp_arr = realloc(temp_arr, num * sizeof(*temp_arr));
      temp_arr[num - 1] = i;
    }
  }
  if (num % 2 == 1) {
    perror("The Number of the replace symbol must be an even number");
    exit(EXIT_FAILURE);
  }
  hist = store_cate(temp_arr, num, line, len, hist, cat, argc);
  free(temp_arr);
  return hist;
}

//free category 
void freecate(category_t * hist) {
  for (size_t g = 0; g < hist->n_words; g++) {
	free(hist->words[g]);
  }
  free(hist->words);
  free(hist);
}

//read both the story and the category with two argument inputs
void read_replace(FILE * f1, FILE * f2, int argc) {
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  category_t * hist = createCate();
  catarray_t * catarray = createCat();
  while ((len = getline(&line, &sz, f1)) >= 0) {
    catarray = getCate(line, catarray);
  }
  while ((len = getline(&line, &sz, f2)) >= 0) {  //story template
    hist = wait_for_replace(line, len, hist, catarray, argc);
  }
  freecate(hist);
  freecat(catarray);
  free(line);
}

//read the story if only one argument input
void readstory(FILE * f) {
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  char * out_arr = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    replace(line, len);
  }
  free(out_arr);
  free(line);
}

//read the category if only one qrgument input
void readcategory(FILE * f) {
  catarray_t * cate = createCat();
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    cate = getCate(line, cate);
  }
  printWords(cate);
  freecat(cate);
  free(line);
}
