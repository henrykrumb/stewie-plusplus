/**
 * application.h - Application class declaration
 * 
 * 
 * 
 * Usually, only one Application object is created per session.
 * There is no mechanism that prevents the developer from creating
 * multiple Application instances, but there should be no rational reason
 * to do so, anyway.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "event.h"
#include "frame.h"
#include "widget.h" // for MAKE_ADDRESS macro


#define EVENT_NEXT_FRAME "next frame"
#define EVENT_PREVIOUS_FRAME "previous frame"
#define EVENT_SWITCH_FRAME "switch frame"
#define EVENT_QUIT "quit"

/**
 * Application status codes; those are returned by the
 * Application::run() method.
 */
#define APP_STATUS_NO_FRAMES -1
#define APP_STATUS_OK 0
#define APP_STATUS_USER_QUIT 1
#define APP_STATUS_LAST_FRAME 2
#define APP_STATUS_EVENT_QUIT 3


std::string application_status_to_string(int status);


class Application: public EventNode {
public:
	Application(std::string address="");
	Application(const Application&) = delete;
	virtual ~Application() {}
	
	/* inherited from EventNode base class */
	virtual void handle_event(const Event& event);
	
	void add_frame(std::shared_ptr<Frame> frame);
	int run();

protected:
	void p_switch_frame(std::vector<std::shared_ptr<Frame>>::iterator it);
	
	static int s_instances;
	
	bool m_quit;
	int m_status;
	
	std::vector<std::shared_ptr<Frame>> m_frames;
	std::vector<std::shared_ptr<Frame>>::iterator m_frame_iter;
};

