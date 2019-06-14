#include <iostream>

#include "../include/stewie++.h"

#include "example_1.h"


int example_1(int argc, char* argv[]) {
	Application app;
	
	auto frame = std::make_shared<Frame>();
	auto form = std::make_shared<Form>();
	
	auto chk_filter_ac_wide = std::make_shared<CheckBox>("ac wide");
	form->add_child(std::dynamic_pointer_cast<Widget>(chk_filter_ac_wide));
	
	auto chk_filter_ac_narrow = std::make_shared<CheckBox>("ac narrow");
	form->add_child(std::dynamic_pointer_cast<Widget>(chk_filter_ac_narrow));
	
	frame->add_child(std::dynamic_pointer_cast<Widget>(form));
	
	app.add_frame(frame);
	
	app.run();
	
	return EXIT_SUCCESS;
}
