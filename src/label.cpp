#include <cmath>

#include "label.h"
#include "utils.h"


Label::Label(std::string label, std::string address):
		Widget(address),
		m_label(label)
{
	MAKE_ADDRESS(Label);
}


void Label::_show(Canvas& canvas) {
	if (!m_label.empty()) {
		Dimension textsize = stringsize(m_label);
		int textx = round((m_box.w() - textsize.w()) / 2.0f);
		int texty = round((m_box.h() - textsize.h()) / 2.0f);
		canvas.draw_text(m_label, m_box.x() + textx, m_box.y() + texty);
	}
}


int Label::_handle_key(const int& c) {
	return c;
}
