#pragma once
#include "containers/container.h"


class ListBox: public Container {
public:
	ListBox(std::string address="");
	ListBox(const ListBox& lb) = delete;
	virtual ~ListBox();
	
	bool _add_child(std::shared_ptr<Widget> child);
	void _pack();

protected:
	int m_visible_entries;
	int m_scroll;
};
