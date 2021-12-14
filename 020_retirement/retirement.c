# include<stdio.h>
# include<stdlib.h>

struct _retire_info{
	int months; // numbers of months it is appicable to 
	double contribution; // how many dollars are contributed from the account per month
	double rate_of_return; // rate of returns
};

typedef struct _retire_info retire_info;

void retirement (int startAge, //in months
		double initial, //initial savings in dollars
		retire_info working, //info about working
		retire_info retired){ // info about bring retired
	//printf(working.months);
	for (; working.months > 0; working.months--) {
		int y = startAge / 12; // integer
		int m = startAge % 12; // reminder
	
		printf("Age %3d month %2d you have $%.2lf\n",y ,m ,initial);

		initial = working.contribution + initial * (1 + working.rate_of_return);
		startAge++;
	}

	for (; retired.months > 0; retired.months--){
		int y = startAge / 12; // integer
		int m = startAge % 12; // reminder 

		printf("Age %3d month %2d you have $%.2lf\n",y ,m ,initial);
		
		initial = retired.contribution + initial * (1 + retired.rate_of_return);
		startAge++;
		
	}
}
int main(void){
	retire_info work;
	retire_info ret;

	work.months = 489;
	work.contribution = 1000;
	work.rate_of_return = 0.045/12;

	ret.months = 384;
        ret.contribution = -4000;
        ret.rate_of_return = 0.01/12;	
	
	retirement(327, 21345.00, work, ret); 
	
	return 0;
}
