#pragma once

#include <string>

#include "canvas.h"
#include "event.h"
#include "geometry.h"

#define STR_IMPL(x) #x
#define STR(x) STR_IMPL(x)
#define MAKE_ADDRESS(x) \
	m_address = address.empty() ? #x "::" STR(s_instances) : address


class Widget: public EventNode {
public:
	Widget(std::string address="");
	Widget(const Widget& widget) = delete;
	virtual ~Widget() {}

	int _handle_key(int c) { return handle_key(c); }
	void _show(Canvas& canvas) { show(canvas); }
	void _pack() { pack(); }
	
	virtual int handle_key(int c) = 0;
	virtual void show(Canvas& canvas) = 0;
	virtual void pack() {};
	
	virtual std::shared_ptr<Widget> get_child(
		std::string address, bool recursive=true) { return nullptr; }
	
	void set_focus(bool focus) {
		m_focused = focus;
	}
	
	bool is_focusable() const { return m_focusable; }
	bool is_focused() const { return m_focused; }
	bool is_visible() const { return m_visible; }

	Box get_box() const { return m_box; }

	void set_box(Box box);
	void set_parent(Widget* parent);

protected:
	Box m_box;
	Widget* m_parent;
	
	static int s_instances;
	
	bool m_focusable;
	bool m_focused;
	bool m_visible;
};
