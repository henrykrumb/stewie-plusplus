#include <curses.h>

#include "hbox.h"


HBox::HBox(std::string address):
		Container(address)
{
	MAKE_ADDRESS(HBox);
}


HBox::~HBox() {
	
}


void HBox::_pack() {
	if (m_children.empty()) {
		return;
	}
	
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	int childwidth = w / m_children.size();
	int i = 0;
	
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		Box box(x + i * childwidth, y, childwidth, h);
		(*it)->set_box(box);
		i++;
	}
}


int HBox::_handle_key(const int& key) {
	switch (key) {
		case KEY_LEFT:
			focus_previous();
			break;
		case KEY_RIGHT:
			focus_next();
			break;
		default: return key;
	}
	return 0;
}
