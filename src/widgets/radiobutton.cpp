#include <cmath>
#include <sstream>

#include "utils.h"

#include "widgets/radiobutton.h"


RadioButton::RadioButton(
	std::string label,
	std::string address):
		Widget(address),
		Evaluatable(label),
		m_label(label),
		m_state(false)
{
	MAKE_ADDRESS(RadioButton);
	m_focusable = true;
	m_center = true;
}


RadioButton::~RadioButton() {
	
}


void RadioButton::select() {
	if (!m_state) {
		auto siblings = ((Container*) m_parent)->get_children();
		for (auto it = siblings.begin(); it != siblings.end(); ++it) {
			auto radiobutton = std::dynamic_pointer_cast<RadioButton>(*it);
			if (radiobutton != nullptr) {
				radiobutton->m_state = false;
			}
		}
		m_state = true;
	}
}


void RadioButton::_show(Canvas& canvas) {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	sstr << "(";
	sstr << (m_state ? "o" : " ");
	sstr << ") " << m_label;
	std::string text = sstr.str();
	
	Dimension d = stringsize(text);
	if (m_center) {
		canvas.draw_text(
			text,
			x + roundi((float) (w - d.w()) / 2.0f),
			y + roundi((float) (h - d.h()) / 2.0f),
			m_focused
		);
	}
	else {
		canvas.draw_text(
			text,
			x,
			y + roundi((float) (h - d.h()) / 2.0f),
			m_focused
		);
	}
}


int RadioButton::_handle_key(const int& key) {
	if (key == ' ' || key == '\n') {
		select();
	}
	return key;
}


void RadioButton::handle_event(const Event& event) {
	
}


EvalVariant RadioButton::evaluate() {
	#ifdef __cpp_lib_variant
	return EvalVariant(m_state);
	#else
	return EvalVariant(std::to_string(m_state));
	#endif
}
