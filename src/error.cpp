#include <iostream>
#include <curses.h>
#include "error.h"


void fatal(std::string message) {
	curs_set(1);
	nocbreak();
	echo();
	keypad(stdscr, 0);
	endwin();
	
	std::cout << "[fatal] " << message << std::endl;
	
	exit(EXIT_FAILURE);
}
