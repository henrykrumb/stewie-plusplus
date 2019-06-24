#include <iostream>

#include "../include/stewie++.h"

#include "example_2.h"


std::shared_ptr<Frame> make_frame_1() {
	auto frame = std::make_shared<Frame>();
	
	auto hbox = std::make_shared<HBox>();
	
	auto lbl_test = std::make_shared<Label>("test");
	ADD_CHILD(hbox, lbl_test);
	
	/* submit */
	auto btn_submit = std::make_shared<Button>("submit", true, "submit");
	ADD_CHILD(hbox, btn_submit);
	
	ADD_CHILD(frame, hbox);
	
	frame->add_listener(
		[&frame] (const Event& e) {
			if (e.get_source() == "submit") {
				frame->send_event(EVENT_NEXT_FRAME, "application");
			}
		}
	);
	
	return frame;
}


int example_2(int argc, char* argv[]) {
	auto app = std::make_shared<Application>("application");
	
	auto frame = make_frame_1();
	
	app->add_frame(frame);
	
	app->run();
	
	return EXIT_SUCCESS;
}
