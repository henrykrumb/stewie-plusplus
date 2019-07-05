#include <curses.h>

#include "canvas.h"


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
	int x = box.x(), y = box.y(), w = box.w(), h = box.h();
	
	color_set(1, nullptr);
	
	for (int fy = 1; fy < h; fy++) {
		draw_char('|', x, fy + y);
		draw_char('|', x + w - 1, fy + y);
	}
	
	for (int fx = 1; fx < w - 1; fx++) {
		draw_char('-', fx + x, y);
		draw_char('-', fx + x, y + h - 1);
	}
	
	draw_char('+', x, y);
	draw_char('+', x + w - 1, y);
	draw_char('+', x + w - 1, y + h - 1);
	draw_char('+', x, y + h - 1);
	
	color_set(0, nullptr);
}


void Canvas::draw_box(Box box, char character) {
	int x = box.x(), y = box.y(), w = box.w(), h = box.h();
	
	color_set(1, nullptr);
	
	for (int fy = 0; fy < h; fy++) {
		for (int fx = 0; fx < w; fx++) {
			draw_char(' ', fx + x, fy + y);
		}
	}
	
	color_set(0, nullptr);
}


void Canvas::draw_scrollbar(Box box, int page, int pages) {
	
}
