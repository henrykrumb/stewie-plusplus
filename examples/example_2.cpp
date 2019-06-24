#include <iostream>

#include "../include/stewie++.h"

#include "example_2.h"


#define MAKE_BUTTON(NAME, LABEL) \
	auto NAME = std::make_shared<Button>(LABEL, #NAME);

#define MAKE_LABEL(NAME, LABEL) \
	auto NAME = std::make_shared<Label>(LABEL, #NAME);


std::shared_ptr<Frame> make_frame_1() {
	auto frame = std::make_shared<Frame>();
	auto vbox = std::make_shared<VBox>();
	
	MAKE_LABEL(lbl_s1, "sensor 1");
	ADD_CHILD(vbox, lbl_s1);
	
	MAKE_LABEL(lbl_s2, "sensor 2");
	ADD_CHILD(vbox, lbl_s2);
	
	MAKE_LABEL(lbl_s3, "sensor 3");
	ADD_CHILD(vbox, lbl_s3);
	
	MAKE_LABEL(lbl_s4, "sensor 4");
	ADD_CHILD(vbox, lbl_s4);
	
	/* submit */
	MAKE_BUTTON(btn_submit, "submit");
	ADD_CHILD(vbox, btn_submit);
	
	MAKE_BUTTON(btn_quit1, "quit");
	ADD_CHILD(vbox, btn_quit1);
	
	ADD_CHILD(frame, vbox);
	
	frame->add_listener("activate",
		[&frame] (const Event& e) {
			if (e.get_source() == "btn_submit") {
				frame->send_event(EVENT_NEXT_FRAME, "application");
			}
			else if (e.get_source() == "btn_quit1") {
				frame->send_event(EVENT_QUIT, "application");
			}
		}
	);
	
	return frame;
}


std::shared_ptr<Frame> make_frame_2(std::shared_ptr<Application> app) {
	auto frame = std::make_shared<Frame>();
	auto vbox = std::make_shared<VBox>();
	
	MAKE_LABEL(lbl_instruction, "choose mode of operation");
	ADD_CHILD(vbox, lbl_instruction);
	
	MAKE_BUTTON(btn_pointcloud, "point cloud");
	ADD_CHILD(vbox, btn_pointcloud);
	
	MAKE_BUTTON(btn_phantom, "phantom based");
	ADD_CHILD(vbox, btn_phantom);
	
	MAKE_BUTTON(btn_sweep, "sweep");
	ADD_CHILD(vbox, btn_sweep);
	
	MAKE_BUTTON(btn_quit2, "quit");
	ADD_CHILD(vbox, btn_quit2);
	
	ADD_CHILD(frame, vbox);
	
	frame->add_listener("activate",
		[&frame] (const Event& e) {
			if (e.get_source() == "btn_pointcloud") {
				frame->send_event(EVENT_NEXT_FRAME, "application");
			}
			else if (e.get_source() == "btn_phantom") {
				frame->send_event(EVENT_NEXT_FRAME, "application");
			}
			else if (e.get_source() == "btn_sweep") {
				frame->send_event(EVENT_NEXT_FRAME, "application");
			}
			else if (e.get_source() == "btn_quit2") {
				frame->send_event(EVENT_QUIT, "application");
			}
		}
	);
	
	return frame;
}


int example_2(int argc, char* argv[]) {
	auto app = std::make_shared<Application>("application");
	
	auto frame_1 = make_frame_1();
	auto frame_2 = make_frame_2(app);
	
	app->add_frame(frame_1);
	app->add_frame(frame_2);
	
	app->run();
	
	return EXIT_SUCCESS;
}
