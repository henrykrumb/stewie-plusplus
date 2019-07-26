#include <curses.h>

#include "containers/tablebox.h"


TableBox::TableBox(int columns, int rows, std::string address):
	Container(address),
	m_columns(columns),
	m_rows(rows)
{
	MAKE_ADDRESS(TableBox);
}


TableBox::~TableBox() {
	
}


void TableBox::_pack() {
	if (m_children.empty()) {
		return;
	}
	
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	int childwidth = w / m_columns;
	int childheight = h / m_rows;
	int column = 0;
	int row = 0;
	
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		Box box(x + column * childwidth, y + row * childheight, childwidth, childheight);
		(*it)->set_box(box);
		column++;
		if (column >= m_columns) {
			column = 0;
			row++;
		}
	}
}


void TableBox::handle_event(const Event& event) {
	
}


int TableBox::_handle_key(const int& key) {
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


Dimension TableBox::get_minimum_dimensions() {
	// TODO return accumulated minimum dim
	return Dimension(m_columns * 3, m_rows * 3);
}
