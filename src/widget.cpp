#include <iostream>
#include <sstream>

#include "widget.h"


int Widget::s_instances = 0;


Widget::Widget(std::string address):
		EventNode(address),
		m_box(0, 0, 0, 0) {
	s_instances++;
}


void Widget::set_box(Box box) {
	m_box = box;
}


void Widget::set_parent(Widget* parent) {
	m_parent = parent;
}
