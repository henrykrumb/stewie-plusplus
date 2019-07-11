#pragma once

#include <string>

#include "canvas.h"
#include "event.h"
#include "geometry.h"
#include "utils.h"


class Widget: public EventNode {
public:
	Widget(std::string address="");
	Widget(const Widget& widget) = delete;
	void operator=(const Widget& widget) = delete;
	virtual ~Widget() {}
	
	virtual int handle_key(const int& c);
	
	virtual void show(Canvas& canvas);
	virtual void pack();
	
	virtual int _handle_key(const int& c) = 0;
	virtual void _show(Canvas& canvas) = 0;
	virtual void _pack() {};
	
	virtual std::shared_ptr<Widget> get_child(
		std::string address,
		bool recursive=true) { return nullptr; }
	
	virtual void set_focus(const bool& focus) { m_focused = focus; }
	bool is_focusable() const { return m_focusable; }
	bool is_focused() const { return m_focused; }
	
	bool is_visible() const { return m_visible; }
	void set_visible(bool visible) { m_visible = visible; }
	
	Box get_box() const { return m_box; }
	void set_box(Box box);
	void set_parent(Widget* parent);

protected:
	std::string m_content;
	Box m_box;
	
	/*
	 * This needs to be a standard C pointer, as we want to pass it "this"
	 * pointers to parent Widget objects. Creating smart pointer instances
	 * from "this" pointers is tedious, so we use C pointers in this case.
	 */
	Widget* m_parent;
	
	bool m_focusable;
	bool m_focused;
	bool m_visible;
	bool m_active;
	bool m_enabled;
};
