#include <iostream>

#include "frame.h"


Frame::Frame(std::string address):
		Container(address)
{
	MAKE_ADDRESS(Frame);
}


bool Frame::add_child(std::shared_ptr<Widget> widget) {
	if (m_children.size() > 1) {
		throw std::runtime_error("Frames can only have one child");
	}
	return true;
}


void Frame::pack() {
	if (!m_children.empty()) {
		m_children[0]->set_box(m_box);
	}
}


int Frame::handle_key(int c) {
	return c;
}
