#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
	size_t maxseq = 0;
	size_t temp_num[n];
	
	if (n == 0) {
		return 0;
	}

	if (n == 1) {
		return 1;
	}
	
	for (size_t k = 0; k < n; k++) {
		temp_num[k] = 0;
	}

	for (size_t k = 0; k < n - 1; k++) {
		if (array[k] < array[k + 1]) {
			maxseq++;
		}
		else {
			maxseq = 0;
		}
		temp_num[k] = maxseq + 1;				  
	}

	size_t max = temp_num[0];
	for (size_t k = 1; k < n; k++) {
		if (temp_num[k] > max) {
			max = temp_num[k];
		}
	}
	return max;
}
