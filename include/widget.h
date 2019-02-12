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
	Widget(Box box, std::string address="");
	Widget(const Widget& widget) = delete;
	virtual ~Widget() {}

	int handle_key(int c) { return i_handle_key(c); }
	void show(Canvas& canvas) { i_show(canvas); }
	void pack() { i_pack(); }
	
	virtual int i_handle_key(int c) = 0;
	virtual void i_show(Canvas& canvas) = 0;
	virtual void i_pack() {};
	
	bool is_focusable() const { return m_focusable; }
	bool is_focused() const { return m_focused; }
	bool is_visible() const { return m_visible; }

protected:
	Box m_box;
	
	static int s_instances;
	
	bool m_focusable;
	bool m_focused;
	bool m_visible;
};
