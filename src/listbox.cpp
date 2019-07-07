#include <iostream>

#include "containers/listbox.h"


ListBox::ListBox(std::string address):
		Container(address)
{
	MAKE_ADDRESS(ListBox);
}


ListBox::~ListBox() {

}


bool ListBox::_add_child(std::shared_ptr<Widget> child) {
	if (!child->is_focusable()) {
		throw std::runtime_error("ListBox children must be focusable");
	}
	return true;
}


void ListBox::_pack() {
	if (m_children.empty()) {
		return;
	}
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	int childheight = h / m_visible_entries;
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		(*it)->set_visible(false);
	}
}
