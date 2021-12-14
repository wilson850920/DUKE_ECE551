#include <exception>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

#include "class.h"

int main(int argc, char ** argv){
	if (argc != 2) {
		std::cerr << "Please input the correct file" << std::endl;
		exit(EXIT_FAILURE);
	}

	read_dir(argv[1]);

	return EXIT_SUCCESS;
}
