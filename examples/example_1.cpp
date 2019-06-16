#include <iostream>

#include "../include/stewie++.h"

#include "example_1.h"


int example_1(int argc, char* argv[]) {
	auto app = std::make_shared<Application>("application");
	
	auto frame = std::make_shared<Frame>();
	auto form = std::make_shared<VBox>();
	
	
	auto box_ac = std::make_shared<HBox>();
	/* filter AC wide */
	auto chk_filter_ac_wide = std::make_shared<CheckBox>("ac wide");
	ADD_CHILD(box_ac, chk_filter_ac_wide);
	
	/* filter AC narrow */
	auto chk_filter_ac_narrow = std::make_shared<CheckBox>("ac narrow");
	ADD_CHILD(box_ac, chk_filter_ac_narrow);
	
	ADD_CHILD(form, box_ac);
	
	/* filter DC */
	auto chk_filter_dc = std::make_shared<CheckBox>("dc");
	ADD_CHILD(form, chk_filter_dc);
	
	std::vector<std::string> options { "20", "60", "80", "120", "200" };
	auto opt_frequency = std::make_shared<OptionBox>("freq", options);
	ADD_CHILD(form, opt_frequency);
	
	auto prg_1 = std::make_shared<ProgressBar>("progress", "progress");
	prg_1->set_progress(0.5f);
	ADD_CHILD(form, prg_1);
	
	/* submit */
	auto btn_submit = std::make_shared<Button>("submit", true, "submit");
	ADD_CHILD(form, btn_submit);
	
	ADD_CHILD(frame, form);
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
		try {
			bool bvalue = std::get<bool>(it->second);
			std::cout << it->first << ":\t" << bvalue << std::endl;
		}
		catch (const std::bad_variant_access& bva) {
			try {
				std::string svalue = std::get<std::string>(it->second);
				std::cout << it->first << ":\t" << svalue << std::endl;
			} catch (const std::bad_variant_access& bva2) {
				float fvalue = std::get<float>(it->second);
				std::cout << it->first << ":\t" << fvalue << std::endl;
			}
		}
	}
	
	return EXIT_SUCCESS;
}
