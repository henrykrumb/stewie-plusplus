#include <fstream>
#include <iostream>
#include <sstream>

#include "example_json.h"

#include "../include/stewie++.h"


int example_json(int argc, char* argv[]) {
	auto app = Application::instance();
	
	std::ifstream ui("../examples/example_json.json");
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
