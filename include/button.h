#pragma once

#include "widget.h"


class Button: public Widget {
public:
	Button(std::string label, bool center=true, std::string address="");
	Button(const Button&) = delete;
	virtual ~Button() {}

	int _handle_key(const int& key);
	void _show(Canvas& canvas);


protected:
	std::string m_label;
	bool m_center;
};
