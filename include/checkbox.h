#pragma once
#include "event.h"
#include "widget.h"


class CheckBox: public Widget {
public:
	CheckBox(
		std::string label,
		bool state=false,
		bool center=true,
		std::string address=""
	);
	CheckBox(const CheckBox&) = delete;
	virtual ~CheckBox() {}
	
	virtual void handle_event(const Event& event);
	
	virtual int _handle_key(const int& c);
	virtual void _show(Canvas& canvas);

protected:
	std::string m_label;
	bool m_state;
	bool m_center;
};
