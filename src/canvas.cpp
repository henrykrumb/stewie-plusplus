#include <curses.h>

#include "../include/canvas.h"


Canvas::Canvas(bool use_unicode):
		m_use_unicode(use_unicode)
{
	
}


void Canvas::draw_char(char c, int x, int y) {
	mvaddch(y, x, c);
}


void Canvas::draw_text(std::string str, int x, int y) {
	mvaddstr(y, x, str.c_str());
}


void Canvas::draw_frame(Box box, bool thick) {
	
}


void Canvas::draw_box(Box box, char character) {
	
}


void Canvas::draw_scrollbar(Box box, int page, int pages) {
	
}
