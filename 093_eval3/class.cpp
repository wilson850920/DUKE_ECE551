#include "class.h"

// parse name to get current page number
std::string parse_dir_page(std::string temp, std::string del, int par){
	size_t pos = 0;
	std::string token;
	while ((pos = temp.find(del)) != std::string::npos) {
		    token = temp.substr(0, pos);
		    if (par == 0){
			    return token;
		    }
		    temp.erase(0, pos + del.length());
	}
	return temp;
}

//convert string to int
int StringToInt(std::string str){
	int i;
	std::istringstream(str) >> i;
	return i;
}

//check if the page number is valid
void check_page_num(std::string n){
	for (size_t i = 0; i < n.size(); i++){
		if (!std::isdigit(n[i])){
			std::cerr << "wrong file name " << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	if (StringToInt(n) <= 0){
		std::cerr << "wrong file name " << std::endl;
		exit(EXIT_FAILURE);
	}

}

// checl if the page is in correct name format
void check_input_format(char * file){
	std::string file_name(file);
	std::string end = ".txt";
	std::string start = "page";
	std::size_t look_up = file_name.rfind(end);
	std::size_t front = file_name.rfind(start, look_up);
	std::string page_number = file_name.substr(front + 4, look_up - front - 4);
		std::string grep = parse_dir_page(file_name, ".", 1);

	if (front != 0 && file_name[front - 1] != '/'){
		std::cerr << "Error file name" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (grep != "txt"){
		std::cerr << "Error file name" << std::endl;
		exit(EXIT_FAILURE);
	}
	check_page_num(parse_dir_page(page_number, ".", 0));
}

// read a single page and print the result
std::vector<std::string> Page::read_single_page(std::istream & stream, int step){
    	
	//save_current_page(stream);
	int counter = 1;
	std::vector<std::string> lines;
    	std::string line;
   	if (stream.eof() != 1 && stream.good() != 1) {
    	  std::cerr << "Fail to read file" << std::endl;
    	  exit(EXIT_FAILURE);
    	}

    	while (getline(stream, line)) {
    	  lines.push_back(line);
    	}

     	std::vector<std::string>::const_iterator it = lines.begin();

    	while (it != lines.end()) {
    	  //detemine win or lose or nothing
    	  if ((*it) == "WIN") {
    	    flag = 1;
    	    it++;
    	    break;
    	  }
    	  else if ((*it) == "LOSE") {
    	    flag = 0;
    	    it++;
    	    break;
    	  }
    	  else {
    	    flag = 2;
    	    if ((*it).find("#") != std::string::npos) {
    	      break;
    	    }
    	    option.push_back(*it);

  	    ++it;
	  }
    	}
    	// the current it is the # position
	
	if (step == 1){
		if (flag == 1){
			page_num.push_back("WIN");
			return page_num;
		}
		if (flag == 0){
			page_num.push_back("LOSE");
			return page_num;
		}
		for (size_t i = 0; i < option.size(); i++) {
	    		size_t temp = option[i].find(":");  // return index of :
	    		page_num.push_back(option[i].substr(0, temp));
			input_list.push_back(counter);
			counter++;
      		}
		return page_num;
	}

    	std::vector<std::string>::const_iterator it2 = it + 1;
    	while (it2 != lines.end()) {
    	  text.push_back(*it2);
    	  ++it2;
    	}
    	for (size_t i = 0; i < text.size(); i++) {
    	  std::cout << text[i] << std::endl;
    	}

    	std::cout << "\n";
    	if (flag == 1) {
    	  std::cout << "Congratulations! You have won. Hooray!\n";
	  return page_num;
    	}
    	else if (flag == 0) {
    	  std::cout << "Sorry, you have lost. Better luck next time!\n";
	  return page_num;
    	}
    	else {
    	  std::cout << "What would you like to do?\n";
    	  std::cout << "\n";
    	  for (size_t i = 0; i < option.size(); i++) {
    	    size_t temp = option[i].find(":");  // return index of :
	    page_num.push_back(option[i].substr(0, temp));

    	    std::cout << " " << counter << ". " << option[i].substr(temp + 1, option[i].npos)
    	              << "\n";
	    input_list.push_back(counter);
	    
    	    counter++;
	  }
	}
	return page_num;
}

// check if page1 exists, if not, then exit
void check_page1_exist(std::string dir){
	std::string page1 = dir + "/page1.txt";
	std::ifstream ifile(page1.c_str());
	if (!ifile.is_open()){
		std::cerr << "Page1 doesn't exists or you got the wrong name for the story" << std::endl;
		exit(EXIT_FAILURE);
	}
}

// converting an int number into a string
std::string IntToString(int number) {
		std::ostringstream oss;
   	oss<< number;
	return oss.str();
}	  

// read through the directory and list the valid pages for the story
std::vector<std::string> get_valid_page_range(std::string dir){
	std::vector<std::string> valid_range;
	std::string front_name = dir + "/page";
	std::string back_name = ".txt";
	int valid_page_num = 1;
	std::string current_name = front_name + IntToString(valid_page_num) + back_name;
	std::ifstream temp_name(current_name.c_str());

	while (temp_name.eof() || temp_name) {
		valid_range.push_back(current_name);
		valid_page_num ++;
		
		current_name = front_name + IntToString(valid_page_num) + back_name;
		std::ifstream temp_name(current_name.c_str());
		if (!temp_name.eof() && !temp_name){
			break;
		}
	}
	return valid_range;
}

// check if the valid pages were all referred
void check_if_referred(std::vector<std::string> refer, std::vector<std::string> valid, std::string dir){
	for (std::vector<std::string>::iterator it = refer.begin(); it != refer.end(); ++it){
		std::string file_name = dir + "/page" + *it + ".txt";
		std::vector<std::string>::iterator it1;
		it1 = std::find(valid.begin(), valid.end(), file_name);
		if (it1 != valid.end()){
			valid.erase(it1);
		}
	}

	if (valid.size() != 0){
		std::cerr << "There is a file that was not referreed by any other file" << std::endl;
		exit(EXIT_FAILURE);
	}
}

// check if meets all the functions in step2 point4
void create_valid_page_option(std::string dir, std::vector<std::string> valid_page, int step){
	int check_win = 0;
	int check_lose = 0;
	std::vector<std::string> refer_list;
	refer_list.push_back(IntToString(1));
	for (std::vector<std::string>::iterator it = valid_page.begin(); it != valid_page.end(); ++it){
		std::string temp = *it;
		std::ifstream hello(temp.c_str());
		Page p1;
		std::vector<std::string> temp_list = p1.read_single_page(hello, 1);
		
		for (std::vector<std::string>::iterator it2 = temp_list.begin(); it2 != temp_list.end(); ++it2){

			if (*it2 == "WIN"){
				check_win ++;
			}else if (*it2 == "LOSE"){
				check_lose ++;
			}else {
				// create a list with all the referred page number
				std::vector<std::string>::iterator it4;
				it4 = std::find(refer_list.begin(), refer_list.end(), *it2);
				if (it4 == refer_list.end()){
					refer_list.push_back(*it2);
				}
				// check if the option file exists
				std::string check_name = dir + "/page" + *it2 + ".txt";
				std::vector<std::string>::iterator it3;
				it3 = std::find(valid_page.begin(), valid_page.end(), check_name);
				if (it3 == valid_page.end()){
					std::cerr << "File not valid" << std::endl;
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	if (step == 2){
		check_if_referred(refer_list, valid_page, dir);
	}
	if (check_lose == 0){
		std::cerr << "There is no win or lose in this directory" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (check_win == 0){
		std::cerr << "There is no win or win in this directory" << std::endl;
		exit(EXIT_FAILURE);
	}

}

// read the input from the user and continue reading
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

// start reading the story
void read_story(std::string dir){
	std::string final_name = dir + "/page1.txt";
	while(true){
		int count_len = 0;
		std::ifstream first(final_name.c_str());
		std::vector<std::string> pick_a_num;
		Page read;
		pick_a_num = read.read_single_page(first, 0);
		first.close();
		
		for (std::vector<std::string>::iterator it = pick_a_num.begin(); it != pick_a_num.end(); ++it){
			count_len ++;
		}
		if (pick_a_num.size() == 0){
			break;
		}
		int go_to_page = get_input(count_len);
		final_name = dir + "/page" + pick_a_num[go_to_page - 1] + ".txt"; 
	}
}

// read the input directory with all the conditions
void read_dir(std::string dir){
	check_page1_exist(dir);
	std::vector<std::string> valid_page = get_valid_page_range(dir);
	create_valid_page_option(dir, valid_page, 2);
	read_story(dir);
	return;	
}

// compare the options with the page_nums to make sure the result matches
std::string add_input_option(std::string curr, std::string next, std::vector<Page> page){
	std::string output;
	for (size_t k = 0; k < page[StringToInt(curr) - 1].input_list.size(); k ++){
		int pick = page[StringToInt(curr) - 1].input_list[k];
		if (page[StringToInt(curr) - 1].page_num[pick - 1] == next){
			output = curr + "(" + IntToString(pick) + ")";
		}
	}
	return output;
}

// get the route of the win pages and print the route
void print_route(std::vector<Page> page){
	for (size_t t = 0; t < page.size(); t ++){
		if (page[t].page_num[0] == "WIN"){
			std::vector<std::string> win;
			std::string par = page[t].parent;
			std::string cur = page[t].current_page;
			win.push_back(cur);
			while(par.size() != 0){
				win.push_back(par);
				par = page[StringToInt(par) - 1].parent;  	

			}
			for (int g = win.size() - 1; g > -1; g --){
				if (g == 0){
					std::cout << win[g] << "(win)" << std::endl;
				}else{
					std::string temp = add_input_option(win[g], win[g - 1], page);
					std::cout << temp << ",";
				}
			}
		}
	}
}

// create a bfs-like structure to ensure everyone has been visited
void bfs(std::vector<Page> page, std::vector<std::string> valid, std::vector<std::string> route, std::vector<size_t> size){
	std::vector<std::string> que;
	que.push_back(page[0].current_page);
	int count = 1;
	while(!que.empty()){
		if (que[0] == "WIN" || que[0] == "LOSE"){
			std::vector<std::string>::iterator it = que.begin();
	 		que.erase(it);
			count++;
			continue;
		}
		
		page[(StringToInt(que[0]) - 1)].visit = true;
		for (size_t i = 0; i < page[(StringToInt(que[0]) - 1)].page_num.size(); i ++){
			que.push_back(page[(StringToInt(que[0]) - 1)].page_num[i]);
			if (page[(StringToInt(que[0]) - 1)].page_num[i] == "WIN" || page[(StringToInt(que[0]) - 1)].page_num[i] == "LOSE"){
			}else{
				page[StringToInt(page[(StringToInt(que[0]) - 1)].page_num[i]) - 1].parent = page[(StringToInt(que[0]) - 1)].current_page;
			}
		}
		std::vector<std::string>::iterator it = que.begin();
		que.erase(it);
		count++;
	}
	print_route(page);
}

// go through the routes and see which meets step4's criteria
void visit_option(std::vector<Page> page, std::vector<std::string> valid){
	std::vector<size_t> size;
	std::vector<std::string> route;
	for (size_t k = 0; k < page.size(); k ++){
		int choice = 1;
		std::vector<std::string> num = page[k].page_num;
		size.push_back(num.size());
		if (num.size() == 1 && (num[0] == "WIN" || num[0] == "LOSE")){
			route.push_back(num[0]);
		}
		else{
			for (size_t i = 0; i < num.size(); i ++){
						
				route.push_back(num[i]);
				choice ++;
			}

		}
	}
	
	bfs(page, valid, route, size);
}


//check the dep
void cal_dep(std::vector<Page> page, std::vector<std::string> valid, int step){
	
	std::vector<Page>::iterator it1 = page.begin();
	it1->depth = 0;
	it1->visit = true;
	
	for (size_t k = 0; k < page.size(); k ++){
		std::vector<std::string> num = page[k].page_num;
		std::vector<std::string>::iterator it = num.begin();

		if (*it == "WIN" || *it == "LOSE"){
			continue;
		}

		for (size_t h = 0; h < num.size(); h ++){
			page[StringToInt(num[h]) - 1].parent = page[k].current_page;
			if (step == 3){
				if (page[StringToInt(num[h]) - 1].depth != -1){
					continue;
				}
				page[StringToInt(num[h]) - 1].depth = page[k].depth + 1;
				if (StringToInt(page[StringToInt(num[h]) - 1].parent) == 1){
					page[StringToInt(num[h]) - 1].visit = true;
				}
			}
		}
	}
			
	if (step == 3){
		for (std::vector<Page>::iterator it = page.begin(); it != page.end(); ++ it){
			if ((it != page.begin() && it->depth == 0) || (it->depth == 1 && it->visit == false) || it->depth == -1){
				std::cout << "Page " << it->current_page << " is not reachable" << std::endl;
			}else {
				std::cout << "Page " << it->current_page << ":" << it->depth << std::endl;
			}
		}
	}else {
		visit_option(page, valid);
	}
}

// create a list of page objects
void create_Page(std::string dir, std::vector<std::string> valid, int step){
	std::vector<Page> page_list;
	
	for (std::vector<std::string>::iterator it = valid.begin(); it != valid.end(); ++it){
		std::string temp = *it;
		std::string cur;
		cur = parse_dir_page(parse_dir_page(parse_dir_page(temp, "/", 1), "e", 1), ".", 0);
		std::ifstream file(temp.c_str());
		
		Page * temp_page = new Page();
		temp_page->current_page = cur;
		std::vector<std::string> num = temp_page->read_single_page(file, 1);
		page_list.push_back(*temp_page);

		delete temp_page;
	}

	cal_dep(page_list, valid, step);
}

// start checking conditions for step3
void read_dir_step3(std::string dir){
	check_page1_exist(dir);
	std::vector<std::string> valid_page = get_valid_page_range(dir);
	create_valid_page_option(dir, valid_page, 3);
	create_Page(dir, valid_page, 3);
	
}

// start functions for step4
void read_dir_step4(std::string dir){
	check_page1_exist(dir);
	std::vector<std::string> valid_page = get_valid_page_range(dir);
	create_valid_page_option(dir, valid_page, 3);
	create_Page(dir, valid_page, 4);	
}

