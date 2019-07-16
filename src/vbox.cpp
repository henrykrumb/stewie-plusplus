#include <curses.h>

#include "containers/vbox.h"


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


Dimension VBox::get_minimum_dimensions() {
	int min_w = m_min_dimensions.w(), min_h = m_min_dimensions.h();
	// accumulated minimum height
	int acc_h = 0;
	
	for(auto& child: m_children) {
		auto child_dmin = child->get_minimum_dimensions();
		
		if (min_w < child_dmin.w()) {
			min_w = child_dmin.w();
		}
		acc_h += child_dmin.h();
	}
	
	if (min_h < acc_h) {
		min_h = acc_h;
	}
	
	return Dimension(min_w, min_h);
}
