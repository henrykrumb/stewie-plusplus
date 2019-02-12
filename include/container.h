#pragma once

#include <vector>

#include "geometry.h"
#include "widget.h"


class Container: public Widget {
public:
	Container(Box box, std::string address="");
	Container(const Container& c);
	virtual ~Container() {}
	
	virtual void i_show(Canvas& canvas) {}

	bool add_child(std::shared_ptr<Widget> widget);
	virtual bool i_add_child(std::shared_ptr<Widget> widget) {
		return true;
	}

	bool remove_child(std::shared_ptr<Widget> widget);
	virtual bool i_remove_child(std::shared_ptr<Widget> widget) {
		return true;
	}

	void get_child(std::string address, bool recursive=true);

	std::size_t children();

protected:
	int m_focused_child;
	std::vector<std::shared_ptr<Widget>> m_children;
};
