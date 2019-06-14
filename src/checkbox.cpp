#include <cstdlib>
#include <sstream>

#include "checkbox.h"
#include "error.h"
#include "utils.h"


CheckBox::CheckBox(
	std::string label,
	bool state,
	bool center,
	std::string name,
	std::string address
):
		Widget(address),
		Evaluatable(name),
		m_label(label),
		m_state(state),
		m_center(center)
{
	MAKE_ADDRESS(CheckBox);
	m_focusable = true;
}


void CheckBox::handle_event(const Event& event) {
	
}


int CheckBox::_handle_key(const int& c) {
	if (c == ' ') {
		m_state = !m_state;
		send_event("activate");
		return 0;
	}
	return c;
}


void CheckBox::_show(Canvas& canvas) {
	canvas.draw_frame(m_box);
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	if (m_focused) {
		sstr << ">> ";
	}
	else {
		sstr << "   ";
	}
	sstr << "[";
	if (m_state) {
		sstr << "x";
	}
	else {
		sstr << " ";
	}
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


eval_variant CheckBox::evaluate() {
	return eval_variant(m_state);
}
