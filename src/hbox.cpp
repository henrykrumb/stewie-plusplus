#include <curses.h>

#include "containers/hbox.h"


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


Dimension HBox::get_minimum_dimensions() {
	int min_w = m_min_dimensions.w(), min_h = m_min_dimensions.h();
	// accumulated minimum height
	int acc_w = 0;
	
	for(auto& child: m_children) {
		auto child_dmin = child->get_minimum_dimensions();
		
		if (min_h < child_dmin.h()) {
			min_h = child_dmin.h();
		}
		acc_w += child_dmin.w();
	}
	
	if (min_w < acc_w) {
		min_w = acc_w;
	}
	
	return Dimension(min_w, min_h);
}
