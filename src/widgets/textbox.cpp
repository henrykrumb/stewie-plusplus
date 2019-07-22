#include <sstream>

#include <curses.h>

#include "widgets/textbox.h"


TextBox::TextBox(std::string label, std::string address):
		Widget(address),
		Evaluatable(label),
		m_empty(true),
		m_label(label),
		m_text(label),
		m_cursor_x(0),
		m_cursor_y(0)
{
	MAKE_ADDRESS(TextBox);
	m_focusable = true;
	m_editable = true;
}


TextBox::~TextBox() {
	
}


void TextBox::handle_event(const Event& event) {
	
}


int TextBox::_handle_key(const int& key) {
	Dimension d = stringsize(m_text);
	
	if (isgraph(key) || key == ' ') {
		if (m_empty) {
			m_text = "";
			m_empty = false;
			m_cursor_x = 0;
			m_cursor_y = 0;
		}
		m_text = m_text.insert(m_cursor_x, std::string(1, key));
		m_cursor_x++;
		return 0;
	}
	else if (key == '\t') {
		// FIXME use real tabs instead of a fixed number of spaces
		if (m_empty) {
			m_text = "";
			m_empty = false;
			m_cursor_x = 0;
			m_cursor_y = 0;
		}
		m_text = m_text.insert(m_cursor_x, "    ");
		m_cursor_x += 4;
		return 0;
	}
	/*else if (key == '\n') {
		m_text = m_text.insert(m_cursor_y, "\n");
		m_cursor_x = 0;
		m_cursor_y++;
	}*/
	else if (key == KEY_LEFT) {
		if (m_empty) {
			return key;
		}
		if (m_cursor_x <= 0) {
			return key;
		}
		m_cursor_x--;
		return 0;
	}
	else if (key == KEY_RIGHT) {
		if (m_empty) {
			return key;
		}
		if (m_cursor_x >= (int) m_text.size()) {
			return key;
		}
		m_cursor_x++;
		return 0;
	}
	else if (key == KEY_UP) {
		if (m_empty) {
			return key;
		}
		if (m_cursor_y <= 0) {
			return key;
		}
		m_cursor_y--;
		return 0;
	}
	else if (key == KEY_DOWN) {
		if (m_empty) {
			return key;
		}
		if (m_cursor_y >= d.h() - 1) {
			return key;
		}
		m_cursor_y++;
		return key;
	}
	else if (key == KEY_BACKSPACE) {
		if (m_cursor_x > 0) {
			m_text = m_text.erase(m_cursor_x - 1);
			m_cursor_x--;
			if (m_text.empty()) {
				m_empty = true;
				m_text = m_label;
				m_cursor_x = 0;
			}
			return 0;
		}
	}
	return key;
}


void TextBox::_show(Canvas& canvas) {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	std::stringstream sstr;
	
	Dimension d = stringsize(m_text);
	canvas.draw_text(
		m_text,
		x + roundi((float) (w - d.w()) / 2.0f),
		y + roundi((float) (h - d.h()) / 2.0f),
		(m_focused == m_empty)
	);
	
	if (m_focused) {
		char c = '_';
		if (m_cursor_x < (int) m_text.size()) {
			c = m_text[m_cursor_x];
		}
		int texth = d.h() ? d.h() : 1;
		canvas.draw_char(
			c,
			x + roundi((float) (w - d.w()) / 2.0f) + m_cursor_x,
			y + roundi((float) (h - texth) / 2.0f) + m_cursor_y,
			true
		);
	}
}


EvalVariant TextBox::evaluate() {
	if (m_empty) {
		return EvalVariant("");
	}
	return EvalVariant(m_text);
}
