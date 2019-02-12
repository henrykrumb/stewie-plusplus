#include <iostream>
#include <sstream>

#include "../include/widget.h"


int Widget::s_instances = 0;


Widget::Widget(Box box, std::string address):
		EventNode(address),
		m_box(box) {
	s_instances++;
}


Widget::Widget(const Widget& widget):
		EventNode(widget),
		m_box(widget.m_box)
{
	
}
