#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sortnPrint(std::istream & stream) {
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	if (!stream.eof() && !stream) {
		std::cerr << "Failed to read file" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::sort(lines.begin(), lines.end());
	typename std::vector<std::string>::const_iterator it = lines.begin();
	while (it != lines.end()) {
		std::cout << *it << std::endl;
		++it;
	}
}

int main(int argc, char ** argv) {
	  if (argc == 1) {
		  sortnPrint(std::cin);
	  }
	  if (argc > 1) {
		  for (int i = 1; i < argc; i++) {
			  std::ifstream input(argv[i]);
			  if (!input) {
				  std::cerr << "Failed to read file" << std::endl;
				  exit(EXIT_FAILURE);
			  }
			  sortnPrint(input);
		  }
	  }
	  return EXIT_SUCCESS;
}
