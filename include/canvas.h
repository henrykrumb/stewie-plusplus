#pragma once

#include <string>

#include "geometry.h"


class Canvas {
public:
	Canvas(bool use_unicode=false);
	Canvas(const Canvas& c) = delete;
	virtual ~Canvas() {}
	
	void draw_char(char c, int x, int y);
	void draw_text(std::string str, int x, int y);
	void draw_frame(Box box, bool thick=false);
	void draw_box(Box box, char character='#');
	void draw_scrollbar(Box box, int page, int pages);

private:
	bool m_use_unicode;
};
