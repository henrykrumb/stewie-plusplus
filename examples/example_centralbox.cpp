#include <functional>
#include <iostream>

#include "../include/stewie++.h"

#include "example_centralbox.h"


#define MAKE_BUTTON(NAME, LABEL) \
	auto NAME = std::make_shared<Button>(LABEL, #NAME);


int example_centralbox(int argc, char* argv[]) {
	auto app = Application::instance();
	
	auto frame = std::make_shared<Frame>("frame");
	auto cbox = std::make_shared<CentralBox>();

	MAKE_BUTTON(btn_top, "top");
	MAKE_BUTTON(btn_middle, "middle");
	
	auto hbox = std::make_shared<HBox>();
	MAKE_BUTTON(btn_bottom, "bottom");
	MAKE_BUTTON(btn_quit, "quit");
	
	ADD_CHILD(cbox, btn_top);
	ADD_CHILD(cbox, btn_middle);
	ADD_CHILD(hbox, btn_bottom);
	ADD_CHILD(hbox, btn_quit);
	ADD_CHILD(cbox, hbox);
	ADD_CHILD(frame, cbox);
	
	frame->add_listener("activate",
		[&frame] (const Event& e) {
			if (e.get_source() == "btn_quit") {
				frame->send_event(APP_EVENT_I_QUIT, "application");
			}
		}
	);
	
	app->add_frame(frame);
	app->run();
	
	return EXIT_SUCCESS;
}
