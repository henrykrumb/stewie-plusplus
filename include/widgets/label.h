#pragma once

#include "widget.h"


#define LABEL_EVENT_I_SET_TEXT "set text"


class Label: public Widget {
public:
	Label(std::string label, std::string address="");
	Label(const Label&) = delete;
	virtual ~Label() {}
	
	virtual void handle_event(const Event& event);
	
	virtual int _handle_key(const int& c);
	virtual void _show(Canvas& canvas);

protected:
	std::string m_label;
};
