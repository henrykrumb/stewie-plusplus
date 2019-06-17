#include <curses.h>

#include "vbox.h"


VBox::VBox(std::string address):
		Container(address)
{
	MAKE_ADDRESS(VBox);
}


VBox::~VBox() {
	
}


void VBox::_pack() {
	if (m_children.empty()) {
		return;
	}
	
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	int childheight = h / m_children.size();
	int i = 0;
	
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		Box box(x, y + i * childheight, w, childheight);
		(*it)->set_box(box);
		i++;
	}
}


int VBox::_handle_key(const int& key) {
	switch (key) {
		case KEY_UP:
			if (!focus_previous()) {
				return key;
			}
			break;
		case KEY_DOWN:
			if (!focus_next()) {
				return key;
			}
			break;
		default: return key;
	}
	return 0;
}
