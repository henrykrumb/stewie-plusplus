#include <curses.h>

#include "application.h"
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


void Application::run() {
	initscr();
	m_frame.set_box(Box(0, 0, COLS, LINES));
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
