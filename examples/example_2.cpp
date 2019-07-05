#include <iostream>

#include "../include/stewie++.h"

#include "example_2.h"


#define MAKE_BUTTON(NAME, LABEL) \
	auto NAME = std::make_shared<Button>(LABEL, #NAME);

#define MAKE_LABEL(NAME, LABEL) \
	auto NAME = std::make_shared<Label>(LABEL, #NAME);


std::shared_ptr<Frame> make_frame_1() {
	auto frame = std::make_shared<Frame>("frame_1");
	auto vbox = std::make_shared<VBox>();
	
	/* submit */
	MAKE_BUTTON(btn_frame_1_submit, "submit");
	ADD_CHILD(vbox, btn_frame_1_submit);
	
	MAKE_BUTTON(btn_frame_1_quit, "quit");
	ADD_CHILD(vbox, btn_frame_1_quit);
	
	ADD_CHILD(frame, vbox);
	
	frame->add_listener("activate",
		[&frame] (const Event& e) {
			if (e.get_source() == "btn_frame_1_submit") {
				frame->send_event(APP_EVENT_I_SWITCH_FRAME, "application", "frame_2");
			}
			else if (e.get_source() == "btn_frame_1_quit") {
				frame->send_event(APP_EVENT_I_QUIT, "application");
			}
		}
	);
	
	return frame;
}


std::shared_ptr<Frame> make_frame_2() {
	auto frame = std::make_shared<Frame>("frame_2");
	auto vbox = std::make_shared<VBox>();
	
	MAKE_BUTTON(btn_quit2, "quit");
	ADD_CHILD(vbox, btn_quit2);
	
	ADD_CHILD(frame, vbox);
	
	frame->add_listener("activate",
		[&frame] (const Event& e) {
			if (e.get_source() == "btn_quit2") {
				frame->send_event(APP_EVENT_I_QUIT, "application");
			}
		}
	);
	
	return frame;
}


int example_2(int argc, char* argv[]) {
	auto app = std::make_shared<Application>("application");
	
	auto frame_1 = make_frame_1();
	auto frame_2 = make_frame_2();
	
	app->add_frame(frame_1);
	app->add_frame(frame_2);
	
	app->run();
	
	return EXIT_SUCCESS;
}
