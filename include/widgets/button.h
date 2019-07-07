#pragma once

#include "widget.h"


#define BUTTON_EVENT_O_ACTIVATE "activate"

class Button: public Widget {
public:
	Button(std::string label, std::string address="");
	Button(const Button&) = delete;
	virtual ~Button() {}
	
	virtual void handle_event(const Event& event);
	
	/* inherited from Widget base class */
	virtual int _handle_key(const int& key);
	virtual void _show(Canvas& canvas);


protected:
	std::string m_label;
};
