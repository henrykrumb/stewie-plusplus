#include <iostream>
#include <sstream>

#include "widgets/widget.h"


Widget::Widget(std::string address):
		EventNode(address),
		m_box(0, 0, 0, 0),
		m_min_dimensions(0, 3),
		m_focusable(false),
		m_editable(false),
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
		if (m_editable) {
			canvas.draw_frame(m_box, false, false);
		}
		_show(canvas);
	}
}


void Widget::pack() {
	_pack();
}
