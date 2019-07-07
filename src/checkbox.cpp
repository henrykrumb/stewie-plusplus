#include <cmath>
#include <cstdlib>
#include <sstream>

#include "error.h"
#include "utils.h"

#include "widgets/checkbox.h"


CheckBox::CheckBox(
	std::string label,
	bool state,
	bool center,
	std::string address
):
		Widget(address),
		Evaluatable(label),
		m_label(label),
		m_state(state),
		m_center(center)
{
	MAKE_ADDRESS(CheckBox);
	m_focusable = true;
}


void CheckBox::handle_event(const Event& event) {
	
}


int CheckBox::_handle_key(const int& key) {
	if (key == ' ' || key == '\n') {
		m_state = !m_state;
		send_event("activate");
		return 0;
	}
	return key;
}


void CheckBox::_show(Canvas& canvas) {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	sstr << "[";
	sstr << (m_state ? "x" : " ");
	sstr << "] " << m_label;
	std::string text = sstr.str();
	
	Dimension d = stringsize(text);
	if (m_center) {
		canvas.draw_text(
			text,
			x + roundi((float) (w - d.w()) / 2.0f),
			y + roundi((float) (h - d.h()) / 2.0f)
		);
	}
	else {
		canvas.draw_text(
			text,
			x,
			y + roundi((float) (h - d.h()) / 2.0f)
		);
	}
}


EvalVariant CheckBox::evaluate() {
	return EvalVariant(m_state);
}
