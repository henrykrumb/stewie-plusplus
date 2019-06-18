#include <cmath>
#include <sstream>

#include "radiobutton.h"
#include "utils.h"


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
	canvas.draw_frame(m_box);
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	if (m_focused) {
		sstr << ">> ";
	}
	else {
		sstr << "   ";
	}
	sstr << "(";
	sstr << (m_state ? "o" : " ");
	sstr << ") " << m_label;
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


int RadioButton::_handle_key(const int& key) {
	if (key == ' ' || key == '\n') {
		select();
	}
	return key;
}


void RadioButton::handle_event(const Event& event) {
	
}


EvalVariant RadioButton::evaluate() {
	return EvalVariant(m_state);
}
