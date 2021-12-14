#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include<stdio.h>
#include "provided.h"
//any functions you want your main to use

void read_replace(FILE * f1, FILE * f2, int argc);
void readstory(FILE * f);
void readcategory(FILE * f);
ssize_t * checkrep(const char * line, ssize_t len, ssize_t * rep_arr);
void replace(const char * line, ssize_t len);
void organize(ssize_t * rep_arr, int numrep, const char * line, ssize_t len);
void findspace(const char * line, char * array, ssize_t n);	
catarray_t * createCat(void);
//category_t * createCate(void);
catarray_t * getCate(const char * line, catarray_t * cate);
char * split_line_cat(const char * line, char split_sym);
char * split_line_word(const char * line, char split_sym);
catarray_t * addCat(catarray_t * cate, char * cat, char * word);
void freecat(catarray_t * cate);
#endif
