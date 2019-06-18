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
	canvas.draw_frame(m_box);
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	
	Dimension d = stringsize(m_label);
	canvas.draw_text(
		m_label,
		x + roundi((float) (w - d.w()) / 2.0f),
		y + roundi((float) (h - d.h()) / 2.0f)
	);
}


int Label::_handle_key(const int& c) {
	return c;
}
