#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "class.h"

int main(int argc, char ** argv){
  if (argc != 2) {
    std::cerr << "Please input the correct file" << std::endl;
    exit(EXIT_FAILURE);
  }
  check_input_format(argv[1]);

  std::ifstream ifs(argv[1], std::ifstream::in);
  if (!ifs.is_open()) {
    std::cerr << "Failed to read file" << std::endl;
    exit(EXIT_FAILURE);
  }
  Page read_page;
  read_page.read_single_page(ifs, 0);

  ifs.close();

  return EXIT_SUCCESS;
}
