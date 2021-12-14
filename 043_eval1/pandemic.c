#include "pandemic.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

country_t parseLine(char * line) {
  //WRITE ME
  	country_t ans;

	//char *test = line;
	char name_list[64]; //= {'\0'};
	int len = strlen(line);
	//int comma = 0;
	//printf("%d\n",len);
	if (len == 1) { 
		perror("Enter country name and population\n");
		exit(EXIT_FAILURE);
	}
	if (strchr(line, ',')  == NULL){
		perror("wrong format, losing comma\n");
		exit(EXIT_FAILURE);
	}

	//printf("%s",name_list);
	
	//for (int i = 0; i < len; i ++) { 
	//	if (line[i] == ','){
	//		comma ++;
	//	}
	//}
	//if (comma > 1){
	//	perror("Please check data, found two commas\n");
	//	exit(EXIT_FAILURE);
	//}


	for (int i = 0; i < len; i ++){
		if (i >= 64){
			perror("Country name too long\n");
			exit(EXIT_FAILURE);
		}
		
		if (line[i] == ','){
			//printf("reach the comma\n");
			break;
		}
		name_list[i] = line[i];
		//printf("i = %d, %s\n",i, &name_list[i]);
		ans.name[i] = name_list[i];
		ans.name[i + 1] = '\0';
		//printf("%ld\n", sizeof(ans.name[0]));
	}
	for (int k = 0; k < len; k ++){
		if (line[k] == ','){
			
			//if (isalpha(&line[k + 1]) != Null){
			//	fprintf(stderr, "de detected character afer comma");
			//}
			if (isalpha(line[k + 1])){
			       perror("Please enter a number\n");
			       exit(EXIT_FAILURE);
			}	       

			int population = atoi(&line[k + 1]);
			ans.population = population;
			//printf("%d\n", a);
		}


	}
	//printf("%ls\n", a);

	return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  		
	int avg_len = n_days - 6;
	//printf("avg_len = %d\n", avg_len);
	//printf("%ld\n", n_days);
	if (n_days < 7){
		//exit(EXIT_FAILURE);
		return;
	}
	
	for (size_t i = 0; i < avg_len; i++) {
	       double total = 0.0;	
	       for (size_t k = 0; k < 7; k++){
			//if (isalpha(data[i+k])){
			//	printf("%d\n", data[i+k]);
			//}
			if (&data[i + k] == NULL){
				perror("Losing a number in the dataset");
				exit(EXIT_FAILURE);
			}

			total += data[i + k];
	       }
	       double average = total / 7;
	       avg[i] = average;
	}

}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
	
	uint64_t pop_per = pop / 100000;
	//printf("per 100,000 = %ld\n", pop_per);	
	double cumu = 0.0;

	if (pop == 0){
		perror("no Pop");
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i< n_days; i ++) {
		
		if (data[i] < 0){
			perror("Cases below 0");
			exit(EXIT_FAILURE);
		}
		
		cumu += data[i];
		//printf("%d\n", cumu);
		cum[i] = cumu / pop_per;
	}
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  	
	int final_country = 0;
	int final_case = 0;
	int count = 0;
	//printf("%d  %d\n", n_countires, n_days);
	if ((n_countries == 0) || (n_days == 0)){
		perror("no countries or days detected");
		exit(EXIT_FAILURE);
	}
		

	for (int i = 0; i < n_days; i ++) {
		int temp_country;
		int cases = 0;
		//int count = 0;
		for (int k = 0; k < n_countries; k ++) {
			if (data[k][i] > cases){
				temp_country = k;
				cases = data[k][i];
			}
		}
		if (cases == final_case) {
			count ++;
		}
		if (cases > final_case) {
			if (count != 0) {
				count = 0;
			}
			final_case = cases;
			final_country = temp_country;
		}


	}

	if (count == 0){
		printf("%s has the most daily cases with %u\n", &countries[final_country].name[0], final_case);
	}else {
		printf("There is a tie between at least two countries\n");
	}

}
