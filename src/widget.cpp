#include <iostream>
#include <sstream>

#include "widget.h"


Widget::Widget(std::string address):
		EventNode(address),
		m_box(0, 0, 0, 0),
		m_focusable(false),
		m_focused(false),
		m_visible(true)
{
	s_instances++;
}


int Widget::handle_key(const int& key) {
	return _handle_key(key);
}


void Widget::set_box(Box box) {
	m_box = box;
}


void Widget::set_parent(Widget* parent) {
	m_parent = parent;
}


void Widget::show(Canvas& canvas) {
	if (m_visible) {
		if (m_focused) {
			canvas.draw_box(m_box);
		}
		_show(canvas);
	}
}


void Widget::pack() {
	_pack();
}


/*void Widget::set_parameters(std::map<std::string, ParameterVariant> p) {
	try {
		ParameterVariant pv_address = p.at("address");
		try {
			std::get<std::string>(pv_address);
		} catch (bad_variant_access& bva) {
			throw std::runtime_error("invalid type for attribute 'address'");
		}
	} catch (out_of_range& oor) {}
	
	
}*/
