#pragma once

#include <memory>
#include <string>
#include <vector>

#include "event.h"
#include "frame.h"
#include "widget.h" // for MAKE_ADDRESS macro


#define EVENT_NEXT_FRAME "next frame"
#define EVENT_PREVIOUS_FRAME "previous frame"
#define EVENT_QUIT "quit"

#define APP_STATUS_NO_FRAMES -1
#define APP_STATUS_OK 0
#define APP_STATUS_USER_QUIT 1
#define APP_STATUS_LAST_FRAME 2
#define APP_STATUS_EVENT_QUIT 3


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
	bool m_quit;
	int m_status;
	
	std::vector<std::shared_ptr<Frame>> m_frames;
	std::vector<std::shared_ptr<Frame>>::iterator m_frame_iter;
};
