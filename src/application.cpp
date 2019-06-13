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


Application::Application() {

}


void Application::add_frame(std::shared_ptr<Frame> frame) {
	m_frames.push_back(frame);
}


void Application::run() {
	initscr();
	m_frames[0]->set_box(Box(0, 0, COLS, LINES));
	m_frames[0]->pack();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, 1);
	timeout(0);
	
	bool quit = false;
	std::atexit(s_exit);
	
	Canvas canvas;
	
	while (!quit) {
		int c = getch();
		
		switch (c) {
			case 'q':
				quit = true;
				break;
			default:
				m_frames[0]->handle_key(c);
				break;
		}
		
		erase();
		m_frames[0]->show(canvas);
		dispatch_events();
	}
}
