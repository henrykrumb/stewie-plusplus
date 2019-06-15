#include <curses.h>

#include <iostream>

#include "application.h"
#include "canvas.h"
#include "error.h"
#include "event.h"
#include "geometry.h"


static void s_exit() {
	curs_set(1);
	nocbreak();
	echo();
	keypad(stdscr, 0);
	endwin();
}


std::string application_status_to_string(int status) {
	switch (status) {
		case APP_STATUS_NO_FRAMES:
			return "no Frame container widgets found in Application";
		case APP_STATUS_OK:
			return "ok";
		case APP_STATUS_USER_QUIT:
			return "quit by user";
		case APP_STATUS_LAST_FRAME:
			return "out of Frame container widgets";
		case APP_STATUS_EVENT_QUIT:
			return "quit by Widget event";
	};
	return "unknown status code";
}



int Application::s_instances = 0;


Application::Application(std::string address):
		EventNode(address),
		m_quit(false),
		m_status(APP_STATUS_OK)
{
	MAKE_ADDRESS(Application);
	s_instances++;
}


/**
 * Add Frame container widget to the Frame list.
 * 
 * \param frame pointer to Frame container widget to append
 */
void Application::add_frame(std::shared_ptr<Frame> frame) {
	m_frames.push_back(frame);
}


void Application::handle_event(const Event& event) {
	if (event.get_id() == EVENT_NEXT_FRAME) {
		m_frame_iter++;
		if (m_frame_iter == m_frames.end()) {
			m_quit = true;
			m_status = APP_STATUS_LAST_FRAME;
		}
	}
	else if (event.get_id() == EVENT_PREVIOUS_FRAME) {
		if (m_frame_iter != m_frames.begin()) {
			m_frame_iter--;
		}
	}
	else if (event.get_id() == EVENT_SWITCH_FRAME) {
		try {
			auto frame = std::get<std::string>(event.get_data());
			for (auto it = m_frames.begin(); it != m_frames.end(); ++it) {
				if ((*it)->get_address() == frame) {
					m_frame_iter = it;
					break;
				}
			}
		} catch (const std::bad_variant_access& a) {
			
		}
	}
	else if (event.get_id() == EVENT_QUIT) {
		m_quit = true;
		m_status = APP_STATUS_EVENT_QUIT;
	}
	else {
		// no matching event
	}
}


/**
 * Run the Application main loop.
 * 
 * Before the actual loop is initiated, the curses terminal environment
 * is set up.
 * 
 * \return status code as defined in the "APP_STATUS_..." definitions
 */
int Application::run() {
	if (m_frames.empty()) {
		return APP_STATUS_NO_FRAMES;
	}
	
	m_frame_iter = m_frames.begin();
	initscr();
	
	auto frame = *(m_frame_iter);
	frame->set_box(Box(0, 0, COLS, LINES));
	frame->pack();
	
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, 1);
	timeout(0);
	
	std::atexit(s_exit);
	
	Canvas canvas;
	
	// TODO add signal handler for SIGINT that properly quits the Application
	
	while (!m_quit) {
		int c = getch();
		
		switch (c) {
			// FIXME maybe widgets want to use the 'q' key as well.
			// possible solution: process 'q' key in Frame objects instead.
			// child widgets can override the 'q' key.
			case 'q':
				m_quit = true;
				m_status = APP_STATUS_USER_QUIT;
				break;
			case KEY_RESIZE:
				frame->set_box(Box(0, 0, COLS, LINES));
				frame->pack();
				break;
			default:
				(*m_frame_iter)->handle_key(c);
				break;
		}
		
		erase();
		(*m_frame_iter)->show(canvas);
		dispatch_events();
	}
	
	s_exit();
	
	return m_status;
}
