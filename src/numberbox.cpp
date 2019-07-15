#include <sstream>

#include <curses.h>

#include "widgets/numberbox.h"


NumberBox::NumberBox(std::string label, std::string address):
		Widget(address),
		Evaluatable(label),
		m_empty(true),
		m_label(label),
		m_value("0"),
		m_cursor(0),
		m_allow_negative(true),
		m_allow_float(true)
{
	MAKE_ADDRESS(NumberBox);
	m_focusable = true;
	m_editable = true;
}


NumberBox::~NumberBox() {
	
}


void NumberBox::handle_event(const Event& event) {
	
}


int NumberBox::_handle_key(const int& key) {
	/* 'key' can be > 255 (e.g. when arrow keys are pressed).
	 * In MSVC standard library, 'isdigit(...)' has a range check assert. */
	if ('0' <= key && key <= '9') {
		if (m_empty) {
			m_value = "";
			m_empty = false;
			m_cursor = 0;
		}
		m_value = m_value.insert(m_cursor, std::to_string(key - '0'));
		m_cursor++;
		return 0;
	}
	else if (key == '-' && m_allow_negative) {
		if (m_cursor == 0) {
			m_value = m_value.insert(m_cursor, "-");
			m_cursor = 1;
		}
		return 0;
	}
	else if (key == '.' && m_allow_float) {
		if (m_value.find('.') == std::string::npos) {
			m_value = m_value.insert(m_cursor, ".");
			m_cursor++;
		}
		return 0;
	}
	else if (key == KEY_LEFT) {
		if (m_empty) {
			return key;
		}
		if (m_cursor <= 0) {
			return key;
		}
		m_cursor--;
		return 0;
	}
	else if (key == KEY_RIGHT) {
		if (m_empty) {
			return key;
		}
		if (m_cursor >= m_value.size()) {
			return key;
		}
		m_cursor++;
		return 0;
	}
	else if (key == KEY_BACKSPACE || key == '\b' || key == 127) {
		if (m_cursor > 0) {
			m_value = m_value.erase(m_cursor - 1);
			m_cursor--;
			if (m_value.empty()) {
				m_empty = true;
				m_value = "0";
				m_cursor = 0;
			}
			return 0;
		}
	}
	else if (key == 'x') {
		if (m_value.size() >= m_cursor) {
			m_value = m_value.erase(m_cursor);
			if (m_value.empty()) {
				m_empty = true;
				m_value = "0";
				m_cursor = 0;
			}
			return 0;
		}
	}
	else if (key == 'd') {
		m_empty = true;
		m_value = "0";
		m_cursor = 0;
		return 0;
	}
	return key;
}


void NumberBox::_show(Canvas& canvas) {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	Dimension d = stringsize(m_value);
	canvas.draw_text(
		m_value,
		x + roundi((float) (w - d.w()) / 2.0f),
		y + roundi((float) (h - d.h()) / 2.0f),
		!m_focused
	);
	
	if (m_focused) {
		char c = '_';
		if (m_cursor < m_value.size()) {
			c = m_value[m_cursor];
		}
		canvas.draw_char(
			c,
			x + roundi((float) (w - d.w()) / 2.0f) + m_cursor,
			y + roundi((float) (h - 1) / 2.0f),
			true
		);
	}
}


float NumberBox::get_value() {
	return std::stof(m_value, nullptr);
}


void NumberBox::set_value(float f) {
	m_value = std::to_string(f);
}


void NumberBox::allow_negative(bool an) {
	m_allow_negative = an;
}


void NumberBox::allow_float(bool af) {
	m_allow_float = af;
}


EvalVariant NumberBox::evaluate() {
	#ifdef __cpp_lib_variant
	return EvalVariant(std::stof(m_value, nullptr));
	#else
	return EvalVariant(m_value);
	#endif
}
