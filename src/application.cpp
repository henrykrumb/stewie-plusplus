#include <curses.h>

#include "../include/application.h"
#include "../include/event.h"
#include "../include/geometry.h"


static void s_exit() {
	curs_set(1);
	nocbreak();
	echo();
	keypad(stdscr, 0);
	endwin();
}


Application::Application():
		m_frame(Box(0, 0, 0, 0)) {
}


void Application::run() {
	initscr();
	m_frame.pack();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, 1);
	timeout(0);
	
	bool quit = false;
	std::atexit(s_exit);
	
	while (!quit) {
		int c = getch();
		if (c == 'q') {
			quit = true;
		}
		
		dispatch_events();
	}
}
