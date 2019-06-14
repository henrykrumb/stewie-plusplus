#include <curses.h>

#include <iostream>

#include "application.h"
#include "canvas.h"
#include "event.h"
#include "geometry.h"


static void s_exit() {
	curs_set(1);
	nocbreak();
	echo();
	keypad(stdscr, 0);
	endwin();
}


Application::Application(std::string address):
		EventNode(address),
		m_quit(false),
		m_status(APP_STATUS_OK)
{
	MAKE_ADDRESS(Application);
}


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
	else if (event.get_id() == EVENT_QUIT) {
		m_quit = true;
		m_status = APP_STATUS_EVENT_QUIT;
	}
	else {
		// no matching event
	}
}


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
	
	while (!m_quit) {
		int c = getch();
		
		switch (c) {
			case 'q':
				m_quit = true;
				m_status = APP_STATUS_USER_QUIT;
				break;
			default:
				(*m_frame_iter)->handle_key(c);
				break;
		}
		
		erase();
		(*m_frame_iter)->show(canvas);
		dispatch_events();
	}
	
	return m_status;
}
