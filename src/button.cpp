#include <cmath>
#include <sstream>

#include "button.h"
#include "error.h"
#include "geometry.h"
#include "utils.h"


Button::Button(std::string label, std::string address):
		Widget(address),
		m_label(label)
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
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	sstr << "[" << m_label << "]";
	std::string text = sstr.str();
	
	Dimension d = stringsize(text);
	canvas.draw_text(
		text,
		x + roundi((float) (w - d.w()) / 2.0f),
		y + roundi((float) (h - d.h()) / 2.0f)
	);
}
