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
	virtual void _show(Canvas& canvas);
	
	virtual int handle_key(const int& c);

	bool add_child(std::shared_ptr<Widget> widget);
	virtual bool _add_child(std::shared_ptr<Widget> widget) {
		return true;
	}

	bool remove_child(std::shared_ptr<Widget> widget);
	virtual bool _remove_child(std::shared_ptr<Widget> widget) {
		return true;
	}

	virtual void pack();

	virtual std::shared_ptr<Widget> get_child(std::string address, bool recursive=true);

	std::size_t children();

	bool focus_first();
	bool focus_next();
	bool focus_previous();

protected:
	std::shared_ptr<Widget> m_focused_child;
	std::vector<std::shared_ptr<Widget>> m_children;
};
