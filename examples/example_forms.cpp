#include <iostream>

#include "../include/stewie++.h"

#include "example_forms.h"


int example_forms(int argc, char* argv[]) {
	auto app = Application::instance();
	
	auto frame = std::make_shared<Frame>();
	auto form = std::make_shared<VBox>();
	
	auto box_food = std::make_shared<HBox>();
	auto lbl_food = std::make_shared<Label>("choose a food item:");
	auto rdb_pizza = std::make_shared<RadioButton>("pizza");
	auto rdb_noodles = std::make_shared<RadioButton>("noodles");
	ADD_CHILD(box_food, lbl_food);
	ADD_CHILD(box_food, rdb_pizza);
	ADD_CHILD(box_food, rdb_noodles);
	
	rdb_pizza->select();
	
	ADD_CHILD(form, box_food);

	auto num_amount = std::make_shared<NumberBox>("amount");
	ADD_CHILD(form, num_amount);
	
	auto chk_cheese = std::make_shared<CheckBox>("add cheese");
	ADD_CHILD(form, chk_cheese);
	
	std::vector<std::string> options { "no sauce", "corn", "onions", "eggplant" };
	auto opt_topping = std::make_shared<OptionBox>("topping:", options);
	ADD_CHILD(form, opt_topping);
	
	auto txt_comments = std::make_shared<TextBox>("comments");
	ADD_CHILD(form, txt_comments);
	
	auto prg_1 = std::make_shared<ProgressBar>("progress", "progress");
	prg_1->set_progress(0.5f);
	ADD_CHILD(form, prg_1);
	
	/* submit */
	auto btn_submit = std::make_shared<Button>("submit", "submit");
	ADD_CHILD(form, btn_submit);
	
	ADD_CHILD(frame, form);
	app->add_frame(frame);
	
	std::map<std::string, EvalVariant> evaluation;
	form->add_listener(
		[form, &evaluation] (const Event& e) {
			if (e.get_source() == "submit") {
				form->send_event(APP_EVENT_I_NEXT_FRAME, "application");
				evaluation = form->evaluate();
			}
		}
	);
	
	app->run();
	
	for (auto it = evaluation.begin(); it != evaluation.end(); ++it) {
		#ifdef __cpp_lib_variant
		try {
			bool bvalue = std::get<bool>(it->second);
			std::cout << it->first << "\t" << bvalue << std::endl;
		}
		catch (const std::bad_variant_access& bva) {
			try {
				std::string svalue = std::get<std::string>(it->second);
				std::cout << it->first << "\t" << svalue << std::endl;
			} catch (const std::bad_variant_access& bva2) {
				try {
					float fvalue = std::get<float>(it->second);
					std::cout << it->first << "\t" << fvalue << std::endl;
				} catch (const std::bad_variant_access& bva3) {
					
				}
			}
		}
		#else
		std::string value = it->second;
		std::cout << it->first << "\t" << value << std::endl;
		#endif
	}
	
	return EXIT_SUCCESS;
}
