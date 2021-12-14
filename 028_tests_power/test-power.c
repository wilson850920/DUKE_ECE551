#include <stdio.h>
#include <stdlib.h>

//void run_check(unsigned x, unsigned y, unsigned expected_ans);

unsigned power (unsigned x, unsigned y);

int run_check(unsigned x, unsigned y, unsigned expected_ans){
	if (power(x,y) != expected_ans) {
		printf("F%d\t", power(x,y));
		exit(EXIT_FAILURE);
	}else{
		printf("S%d\t", power(x,y));
		return EXIT_SUCCESS;
	}
}
int main(void){

	run_check(0, 0, 1);
	run_check(2, 4, 16);
	run_check(10, 3, 1000);
	run_check(-2, 1, -2);
	return 0;
}

