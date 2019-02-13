#pragma once

#include "widget.h"


class CheckBox: public Widget {
public:
	CheckBox(std::string label, bool state=false, std::string address="");
	CheckBox(const CheckBox&) = delete;
	virtual ~CheckBox() {}
};
