#include "container.h"


Container::Container(std::string address):
		Widget(address),
		m_focused_child(nullptr)
{
}


Container::~Container() {
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		(*it)->set_parent(nullptr);
	}
}


bool Container::_add_child(std::shared_ptr<Widget> widget) {
	if (m_focused_child == nullptr && widget->is_focusable()) {
		m_focused_child = widget;
	}
	if (add_child(widget)) {
		widget->set_parent(this);
		m_children.push_back(widget);
		_pack();
	}
}


bool Container::_remove_child(std::shared_ptr<Widget> widget) {
	if (widget == m_focused_child) {
		m_focused_child = nullptr;
	}
}


std::shared_ptr<Widget> Container::get_child(std::string address, bool recursive) {
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		if ((*it)->get_address() == address) {
			return *it;
		}
		if (recursive) {
			std::shared_ptr<Widget> child = (*it)->get_child(address, recursive);
				if (child != nullptr) {
					return child;
				}
			}
	}
	return nullptr;
}


void Container::_pack() {
	pack();
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		(*it)->set_focus(*it == m_focused_child && m_focused);
	}
}


std::size_t Container::children() {
	return m_children.size();
}
