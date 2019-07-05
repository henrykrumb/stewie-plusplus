#include <fstream>
#include <iostream>
#include <sstream>

#include "example_3.h"

#include "../include/stewie++.h"


int example_3(int argc, char* argv[]) {
	auto app = std::make_shared<Application>("application");
	
	std::ifstream ui("../examples/example_3.ui");
	std::stringstream sstr;
	if (ui.is_open()) {
		std::string line;
		while (std::getline(ui, line)) {
			sstr << line << "\n";
		}
	}
	std::string str = sstr.str();
	
	auto frame = read_widgettree(str);
	
	//app->add_frame(frame);
	
	//app->run();
	
	return EXIT_SUCCESS;
}
