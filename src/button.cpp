#include <cmath>
#include <sstream>

#include "button.h"
#include "geometry.h"
#include "utils.h"


Button::Button(std::string label, bool center, std::string address):
		Widget(address),
		m_label(label),
		m_center(center)
{
	MAKE_ADDRESS(Button);
	m_focusable = true;
}


void Button::handle_event(const Event& event) {
	
}


int Button::_handle_key(const int& key) {
	if (key == ' ' || key == '\n') {
		send_event("activate");
		return 0;
	}
	return key;
}


void Button::_show(Canvas& canvas) {
	canvas.draw_frame(m_box);
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	if (m_focused) {
		sstr << ">> ";
	}
	else {
		sstr << "   ";
	}
	sstr << "[" << m_label << "]";
	std::string text = sstr.str();
	
	Dimension d = stringsize(text);
	if (m_center) {
		canvas.draw_text(
			text,
			x + round((float) (w - d.w()) / 2.0f),
			y + round((float) (h - d.h()) / 2.0f)
		);
	}
	else {
		canvas.draw_text(
			text,
			x,
			y + round((float) (h - d.h()) / 2.0f)
		);
	}
}
