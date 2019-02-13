#pragma once

#include "widget.h"


class Button: public Widget {
public:
	Button(std::string label, std::string address="");
	Button(const Button&) = delete;
	virtual ~Button() {}
};
