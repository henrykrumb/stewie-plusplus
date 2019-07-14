#include <curses.h>

#include "canvas.h"


Canvas::Canvas(bool use_unicode):
		m_use_unicode(use_unicode)
{
	
}


void Canvas::draw_char(char c, int x, int y, bool inverse) {
	if (inverse) {
		color_set(1, nullptr);
	}
	mvaddch(y, x, c);
	if (inverse) {
		color_set(0, nullptr);
	}
}


void Canvas::draw_text(std::string str, int x, int y, bool inverse) {
	if (inverse) {
		color_set(1, nullptr);
	}
	mvaddstr(y, x, str.c_str());
	if (inverse) {
		color_set(0, nullptr);
	}
}


void Canvas::draw_frame(Box box, bool thick, bool inverse) {
	int x = box.x(), y = box.y(), w = box.w(), h = box.h();
	
	char c = thick ? '#' : '|';
	for (int fy = 1; fy < h; fy++) {
		draw_char(c, x, fy + y, inverse);
		draw_char(c, x + w - 1, fy + y, inverse);
	}
	
	c = thick ? '#' : '-';
	for (int fx = 1; fx < w - 1; fx++) {
		draw_char(c, fx + x, y, inverse);
		draw_char(c, fx + x, y + h - 1, inverse);
	}
	
	draw_char('+', x, y, inverse);
	draw_char('+', x + w - 1, y, inverse);
	draw_char('+', x + w - 1, y + h - 1, inverse);
	draw_char('+', x, y + h - 1, inverse);
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
