#pragma once

#include <vector>

#include "geometry.h"
#include "widget.h"


class Container: public Widget {
public:
	Container(std::string address="");
	Container(const Container&) = delete;
	virtual ~Container();
	
	virtual void show(Canvas& canvas);

	bool _add_child(std::shared_ptr<Widget> widget);
	virtual bool add_child(std::shared_ptr<Widget> widget) {
		return true;
	}

	bool _remove_child(std::shared_ptr<Widget> widget);
	virtual bool remove_child(std::shared_ptr<Widget> widget) {
		return true;
	}

	virtual void _pack();

	virtual std::shared_ptr<Widget> get_child(std::string address, bool recursive=true);

	std::size_t children();

protected:
	std::shared_ptr<Widget> m_focused_child;
	std::vector<std::shared_ptr<Widget>> m_children;
};
