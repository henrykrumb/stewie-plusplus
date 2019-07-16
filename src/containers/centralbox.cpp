#include <curses.h>

#include "containers/centralbox.h"
#include "containers/container.h"

#include "events/event.h"


/**
 * Standard constructor for CentralBox class.
 * 
 * CentralBoxes are container widgets that comprise a header, a body and
 * a footer widget. The body (in the center) is the largest of the three
 * widgets.
 * If a CentralBox has only a single child, it behaves like a VBox, HBox or
 * Frame, that is the child widget spreads along the whole container.
 * If it has two children, both of them get an equal share of the parent
 * container size.
 */
CentralBox::CentralBox(std::string address):
		Container(address)
{
	MAKE_ADDRESS(CentralBox);
}


CentralBox::~CentralBox() {
	
}


bool CentralBox::_add_child(std::shared_ptr<Widget> widget) {
	if (m_children.size() > 3) {
		throw std::runtime_error("CentralBoxes can only have three children");
	}
	return true;
}


void CentralBox::_pack() {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	
	if (m_children.empty()) {
		return;
	}
	else if (m_children.size() == 1) {
		Box b1(x, y, w, h);
		m_children[0]->set_box(b1);
	}
	else if (m_children.size() == 2) {
		int childheight = h / 2;
		
		Box b1(x, y, w, childheight);
		m_children[0]->set_box(b1);
		
		Box b2(x, y + childheight, w, childheight);
		m_children[1]->set_box(b2);
	}
	else if (m_children.size() == 3) {
		// header
		Box b1(x, y, w, 1);
		m_children[0]->set_box(b1);
		
		// body
		Box b2(x, y + 1, w, h - 2);
		m_children[1]->set_box(b2);
		
		// footer
		Box b3(x, y + h - 1, w, 1);
		m_children[2]->set_box(b3);
	}
}


int CentralBox::_handle_key(const int& key) {
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
