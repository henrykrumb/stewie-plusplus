#include <iostream>

#include "../include/stewie++.h"

#include "example_1.h"


int example_1(int argc, char* argv[]) {
	std::shared_ptr<Application> app;
	app = std::make_shared<Application>("application");
	
	auto frame = std::make_shared<Frame>();
	auto form = std::make_shared<Form>();
	
	/* filter AC wide */
	auto chk_filter_ac_wide = std::make_shared<CheckBox>("ac wide");
	form->add_child(std::dynamic_pointer_cast<Widget>(chk_filter_ac_wide));
	
	/* filter AC narrow */
	auto chk_filter_ac_narrow = std::make_shared<CheckBox>("ac narrow");
	form->add_child(std::dynamic_pointer_cast<Widget>(chk_filter_ac_narrow));
	
	/* filter DC */
	auto chk_filter_dc = std::make_shared<CheckBox>("dc");
	form->add_child(std::dynamic_pointer_cast<Widget>(chk_filter_dc));
	
	/* submit */
	auto btn_submit = std::make_shared<Button>("submit", true, "submit");
	form->add_child(std::dynamic_pointer_cast<Widget>(btn_submit));
	
	frame->add_child(std::dynamic_pointer_cast<Widget>(form));
	app->add_frame(frame);
	
	std::map<std::string, EvalVariant> evaluation;
	app->add_listener(
		[&btn_submit, &form, &evaluation] (const Event& e) {
			if (e.get_source() == "submit") {
				btn_submit->send_event(EVENT_NEXT_FRAME, "application");
				evaluation = form->evaluate();
			}
		}
	);
	
	app->run();
	
	for (auto it = evaluation.begin(); it != evaluation.end(); ++it) {
		std::cout << it->first << ":\t" << std::get<bool>(it->second) << std::endl;
	}
	
	return EXIT_SUCCESS;
}
