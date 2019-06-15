#pragma once

#include "widget.h"


class Button: public Widget {
public:
	Button(std::string label, bool center=true, std::string address="");
	Button(const Button&) = delete;
	virtual ~Button() {}
	
	virtual void handle_event(const Event& event);
	
	/* inherited from Widget base class */
	virtual int _handle_key(const int& key);
	virtual void _show(Canvas& canvas);


protected:
	std::string m_label;
	bool m_center;
};
