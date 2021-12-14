#include <exception>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

#include "cyoa-step1.hpp" 

int main(int argc, char ** argv){
	if (argc != 2){
		perror("Please enter your stroy file");
		exit(EXIT_FAILURE);
	}
	std::ifstream input(argv[1]);
	if (!input){
		std::cerr << "Failed to read file" << std::endl;
		exit(EXIT_FAILURE);
	}
	//read_page(input);

	Page RP;

	RP.read_page(input);
	
	return EXIT_SUCCESS;

}
