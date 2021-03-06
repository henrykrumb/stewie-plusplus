#pragma once

#include <vector>

#include "events/event.h"

#include "evaluatable.h"
#include "geometry.h"

#include "widgets/widget.h"


/* simplify adding shared_ptr|s of Widgets to a Container */
#define ADD_CHILD(parent, child) \
	parent->add_child(std::dynamic_pointer_cast<Widget>(child));


class Container: public Widget {
public:
	Container(std::string address="");
	Container(const Container&) = delete;
	virtual ~Container();
	
	virtual void handle_event(const Event& event) {};
	
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
	
	std::vector<std::shared_ptr<Widget>> get_children() const;
	std::size_t children() const;
	
	virtual std::map<std::string, EvalVariant> evaluate(bool recursive=true);
	
	virtual void set_focus(const bool& focus);
	bool focus_first();
	bool focus_next();
	bool focus_previous();
	
	virtual Dimension get_minimum_dimensions();

protected:
	std::shared_ptr<Widget> m_focused_child;
	std::vector<std::shared_ptr<Widget>> m_children;
};
