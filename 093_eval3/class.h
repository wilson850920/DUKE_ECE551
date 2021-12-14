#ifndef __CLASS_H__
#define __CLASS_H__

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>

//using namespace std;

class Page {
       	public:
		int flag;     // determine win(1), lose(0), conti(2)
		//int counter;  // print the selection from 0
		int depth;    //the depth of a single page
		bool visit;
		std::string parent;
		std::string current_page;
		std::vector<std::string> option;    // the option from the selected page
		std::vector<std::string> page_num;  // corresponding page number from the options
		std::vector<std::string> text;      // story content
		std::vector<int> input_list;
		Page() : depth(-1), visit(false) {};
		~Page(){};
		std::vector<std::string> read_single_page(std::istream & stream, int step);
		//void print_story_content();	


};

void check_input_format(char * file);
void read_dir(std::string dir);
void read_dir_step3(std::string dir);
void read_dir_step4(std::string dir);

#endif
