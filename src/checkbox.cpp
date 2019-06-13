#include <cstdlib>
#include <sstream>

#include "checkbox.h"
#include "utils.h"


CheckBox::CheckBox(
	std::string label,
	bool state,
	bool center,
	std::string address
):
		Widget(address),
		m_label(label),
		m_state(state),
		m_center(center)
{
	MAKE_ADDRESS(CheckBox);
	m_focusable = true;
}


int CheckBox::_handle_key(const int& c) {
	if (c == ' ') {
		m_state = !m_state;
		return 0;
	}
	return c;
}


void CheckBox::_show(Canvas& canvas) {
	canvas.draw_frame(m_box);
	int x = m_box.x();
	int y = m_box.y();
	int w = m_box.w();
	int h = m_box.h();
	std::stringstream sstr;
	
	if (m_focused) {
		sstr << ">> ";
	}
	else {
		sstr << "   ";
	}
	sstr << "[";
	if (m_state)
		sstr << "x";
	else
		sstr << " ";
	sstr << "]";
	sstr << " " << m_label;
	std::string text = sstr.str();
	
	Dimension d = stringsize(text);
	if (m_center) {
		canvas.draw_text(
			text,
			x + (w - d.w()) / 2,
			y + (h - d.h()) / 2
		);
	}
	else {
		canvas.draw_text(
			text,
			x,
			y + (h - d.h()) / 2
		);
	}
}
