#include <functional>
#include <iostream>

#include "../include/stewie++.h"

#include "example_jobs.h"


#define MAKE_BUTTON(NAME, LABEL) \
	auto NAME = std::make_shared<Button>(LABEL, #NAME);


void my_job(Job& j, long iterations) {
	j.set_progress(0.0f);
	
	for (long i = 0; i < iterations; ++i) {
		if (!j.is_running()) {
			break;
		}
		float progress = (float) i / (float) iterations;
		j.set_progress(progress);
	}
}


int example_jobs(int argc, char* argv[]) {
	auto app = Application::instance();
	
	auto frame = std::make_shared<Frame>("frame");
	auto vbox = std::make_shared<VBox>();
	auto prg_job = std::make_shared<ProgressBar>("job progress");
	MAKE_BUTTON(btn_start, "start job");
	MAKE_BUTTON(btn_restart, "restart job");
	MAKE_BUTTON(btn_kill, "kill job");
	MAKE_BUTTON(btn_quit, "quit");
	
	ADD_CHILD(vbox, prg_job);
	ADD_CHILD(vbox, btn_start);
	ADD_CHILD(vbox, btn_restart);
	ADD_CHILD(vbox, btn_kill);
	ADD_CHILD(vbox, btn_quit);
	ADD_CHILD(frame, vbox);
	
	auto job = std::make_shared<Job>(
		std::bind(my_job, std::placeholders::_1, 100000),
		prg_job,
		"my_job"
	);
	register_node(job);
	
	frame->add_listener("activate",
		[&frame, &job] (const Event& e) {
			if (e.get_source() == "btn_start") {
				if (job->get_status() == JOB_STATUS_NONE) {
					frame->send_event(JOB_EVENT_I_START, "my_job");
				}
			}
			else if (e.get_source() == "btn_restart") {
				frame->send_event(JOB_EVENT_I_RESTART, "my_job");
			}
			else if (e.get_source() == "btn_kill") {
				frame->send_event(JOB_EVENT_I_KILL, "my_job");
			}
			else if (e.get_source() == "btn_quit") {
				frame->send_event(APP_EVENT_I_QUIT, "application");
			}
		}
	);
	
	app->add_frame(frame);
	app->run();
	
	return EXIT_SUCCESS;
}
