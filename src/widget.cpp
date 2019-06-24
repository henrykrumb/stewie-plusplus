#include <iostream>
#include <sstream>

#include "widget.h"


int Widget::s_instances = 0;


Widget::Widget(std::string address):
		EventNode(address),
		m_box(0, 0, 0, 0),
		m_focusable(false),
		m_focused(false),
		m_visible(true),
		m_active(true)
{
	s_instances++;
}


int Widget::handle_key(const int& key) {
	if (!m_active) {
		return key;
	}
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
			canvas.draw_frame(m_box);
		}
		 _show(canvas);
	}
}
