#include <stdio.h>
#include <stdlib.h>

size_t  maxSeq(int * array, size_t n);

int check(int * array, size_t n, unsigned expected_ans){
	if (maxSeq(array,n) != expected_ans) {
		printf("F%ld\t", maxSeq(array,n));
		exit(EXIT_FAILURE);
	}else{
		printf("S%ld\t", maxSeq(array,n));
		return EXIT_SUCCESS;
	}
}


int main(void){
	int array1[] = {0,0,0,0};
	///int array2[] = {-2,-1,0,1,2,1,0,-1,-2}; 
	int array3[] = {'A', 'b', 'C'}; 
	int array4[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
	int array5[] = {-1,0,1,2};
	check(array1, 4, 1);
	//check(array2, 9, 5);
	check(array3, 3, 2);
	check(array4, 10, 4);
	check(NULL, 0, 0);
	check(array5, 4,4);

	return 0;
}
