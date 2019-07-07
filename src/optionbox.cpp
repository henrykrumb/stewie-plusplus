#include <cmath>
#include <sstream>

#include "error.h"
#include "utils.h"

#include "widgets/optionbox.h"


OptionBox::OptionBox(
	std::string label,
	std::vector<std::string> options,
	std::string address
):
		Widget(address),
		Evaluatable(label),
		m_label(label),
		m_options(options)
{
	MAKE_ADDRESS(OptionBox);
	m_focusable = true;
	m_center = true;
	if (options.empty()) {
		fatal("OptionBox options must not be empty");
	}
	m_option_iter = m_options.begin();
}


OptionBox::~OptionBox() {
	
}


void OptionBox::handle_event(const Event& event) {
	
}


int OptionBox::_handle_key(const int& c) {
	switch (c) {
		case '+':
			m_option_iter++;
			if (m_option_iter == m_options.end()) {
				m_option_iter--;
			}
			return 0;
		case '-':
			if (m_option_iter != m_options.begin()) {
				m_option_iter--;
			}
			return 0;
		case ' ':
			send_event(EVENT_OPTIONBOX_ACTIVATE, "", *m_option_iter);
			return 0;
		default: return c;
	}
}


void OptionBox::_show(Canvas& canvas) {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	sstr << m_label;
	sstr << " [-] ";
	sstr << *m_option_iter;
	sstr << " [+]";
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


EvalVariant OptionBox::evaluate() {
	std::string option;
	if (m_option_iter == m_options.end()) {
		return EvalVariant("");
	}
	option = *m_option_iter;
	return EvalVariant(option);
}
