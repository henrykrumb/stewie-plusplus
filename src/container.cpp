#include "../include/container.h"


Container::Container(Box box, std::string address):
		Widget(box, address)
{
}


bool Container::add_child(std::shared_ptr<Widget> widget) {
	
}


bool Container::remove_child(std::shared_ptr<Widget> widget) {
	
}


void Container::get_child(std::string address, bool recursive) {
	
}


std::size_t Container::children() {
	return m_children.size();
}
