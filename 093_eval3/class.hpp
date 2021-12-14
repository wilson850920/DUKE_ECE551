#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <typeinfo>

class Page {
 public:

//step1 starts here

    std::vector<std::string> read_page(std::istream & stream){
    //void read_page(std::istream & stream) {    
	std::vector<std::string> text;
	std::vector<std::string> option;
     	std::vector<std::string> page_num;
      	std::vector<std::string> valid_pages;   


	int flag = 0;
    	int counter = 1;
    	//int del = 0;
    	std::vector<std::string> lines;
    	std::string line;
    	while (std::getline(stream, line)) {
    	  lines.push_back(line);
    	  //std::cout << line<< std::endl;
    	}

    	if (!stream.eof() && !stream) {
    	  std::cerr << "Fail to read file" << std::endl;
    	  exit(EXIT_FAILURE);
    	}
    	std::vector<std::string>::const_iterator it = lines.begin();

    	while (it != lines.end()) {
    	  //detemine win or lose or nothing
    	  if ((*it) == "WIN") {
    	    flag = 1;
    	    it++;
    	    break;
    	    //std::cout << "win\n";
    	  }
    	  else if ((*it) == "LOSE") {
    	    flag = 0;
    	    it++;
    	    break;
    	    //std::cout << "lose\n";
    	  }
    	  else {
    	    flag = 2;
    	    if ((*it).find("#") != std::string::npos) {
    	      break;
    	    }
    	    option.push_back(*it);
    	    //std::cout << "text\n";
    	  }
    	  ++it;
    	}
    	// the current it is the # position

    	std::vector<std::string>::const_iterator it2 = it + 1;
    	while (it2 != lines.end()) {
    	  text.push_back(*it2);
    	  ++it2;
    	}
    	//std::cout << flag;
    	for (size_t i = 0; i < text.size(); i++) {
    	  std::cout << text[i] << std::endl;
    	  //std::cout << flag;
    	}

    	std::cout << "\n";
    	if (flag == 1) {
    	  std::cout << "Congratulations! You have won. Hooray!\n";
	  exit(EXIT_SUCCESS);
    	}
    	else if (flag == 0) {
    	  std::cout << "Sorry, you have lost. Better luck next time!\n";
	  exit(EXIT_SUCCESS);
    	}
    	else {
    	  std::cout << "What would you like to do?\n";
    	  std::cout << "\n";
    	  for (size_t i = 0; i < option.size(); i++) {
    	    size_t temp = option[i].find(":");  // return index of :
	    page_num.push_back(option[i].substr(0, temp));

    	    std::cout << " " << counter << ". " << option[i].substr(temp + 1, option[i].npos)
    	              << "\n";
    	    counter++;
    	  }
    	}
	return page_num;
    }

//step2 starts here
	std::string IntToString( int number ) {
      		std::ostringstream oss;
	   	oss<< number;
		return oss.str();
	}	  

    	std::vector<int> get_valid_page_range(std::string stream){
		std::vector<int> valid_range;
		std::string front_name = "./" + stream + "/page";
		std::string back_name = ".txt";
		int valid_page_num = 1;
		std::string current_name = front_name + IntToString(valid_page_num) + back_name;
		std::ifstream temp_name(current_name.c_str());

		while (temp_name.eof() || temp_name) {
			valid_range.push_back(valid_page_num);
			valid_page_num ++;
			
			current_name = front_name + IntToString(valid_page_num) + back_name;
			std::ifstream temp_name(current_name.c_str());
			if (!temp_name.eof() && !temp_name){
				break;
			}
		}

		return valid_range;

	}	

	void read_all_page_noprint(std::string stream, std::vector<int> valid_num){
		std::string file_end_name = ".txt";
		for (std::vector<int>::iterator itva = valid_num.begin(); itva != valid_num.end(); ++itva){	
			std::string file_name = "./" + stream + "/page" + IntToString(*itva) + file_end_name;
			std::ifstream read_all_file(file_name.c_str());
		}

	}

	int get_input(int count_len){

		int temp_num = 0;
		std::string temp_inp = "";
		
		//https://www.cplusplus.com/forum/general/13256/
		while (true) {
			getline(std::cin, temp_inp);
			std::stringstream myStream(temp_inp);
			if ((myStream >> temp_num) && (temp_num > 0 && temp_num <= count_len)){
				break;
			}

			std::cout << "That is not a valid choice, please try again" << std::endl;
			std::cin.clear();
		}	
		return temp_num;
	}

	void read_dir(std::string stream){
		//std::string name = stream;
		std::string end_name =  "/page1.txt";
		std::string final_name;
	        final_name = "./" + stream + end_name;
		

		std::vector<int> valid_num = get_valid_page_range(stream);
		
		//this function is for reading through all the pages without printing
		//refer to README step2 4
		read_all_page_noprint(stream, valid_num);

		while(true){
			//get the corresponding page num of each page
			//std::cout << "name_first:  " << final_name << std::endl; 
			std::ifstream input_file;
			input_file.open(final_name.c_str());
			std::vector<std::string> num;
			num.clear();

			num = read_page(input_file);
			input_file.close();
			
			
			int count_len = 0;
			for (std::vector<std::string>::iterator it = num.begin(); it != num.end(); ++it){
				count_len ++;
			}
			//std::cout << "len: " << count_len << std::endl; 	
			//input_file.close();
			int go_to_page = get_input(count_len);
			
			//assume input 1 to test
			final_name = "./" + stream + "/page" + num[go_to_page - 1] + ".txt";
		}


	}

 };
