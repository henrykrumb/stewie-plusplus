#include <curses.h>

#include "error.h"

#include "containers/banner.h"
#include "widgets/digit.h"


Banner::Banner(std::string text, std::string address):
	Container(address),
	m_text(text)
{
	MAKE_ADDRESS(Banner);
	m_digits = (int) text.size();
}


Banner::~Banner() {
	
}


void Banner::_pack() {
	m_children.clear();
	
	for (int i = 0; i < m_digits; i++) {
		int c = m_text[i];
		m_children.push_back(std::make_shared<Digit>(c));
	}
	
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	int childwidth = 6;
	int i = 0;
	int bx = x + (w - m_children.size() * 6) / 2.0f;
	
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		Box box(bx + i * childwidth, y, childwidth, h);
		(*it)->set_box(box);
		i++;
	}
}


int Banner::_handle_key(const int& key) {
	switch (key) {
		case KEY_LEFT:
			if (!focus_previous()) {
				return key;
			}
			break;
		case KEY_RIGHT:
			if (!focus_next()) {
				return key;
			}
			break;
		default: return key;
	}
	return 0;
}


void Banner::handle_event(const Event& ev) {
	if (ev.get_id() == BANNER_EVENT_I_SET_TEXT) {
		set_text(ev.get_data_as_string());
	}
}


Dimension Banner::get_minimum_dimensions() {
	int min_w = m_min_dimensions.w();
	// accumulated minimum height
	int acc_w = 0;
	
	for(auto& child: m_children) {
		auto child_dmin = child->get_minimum_dimensions();
		acc_w += child_dmin.w();
	}
	
	if (min_w < acc_w) {
		min_w = acc_w;
	}
	
	// TODO replace hardcode
	return Dimension(min_w, 7);
}


void Banner::set_text(const std::string& text) {
	m_text = text;
	m_digits = (int) text.size();
	pack();
}
