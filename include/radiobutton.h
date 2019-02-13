#pragma once

#include "widget.h"


class RadioButton: public Widget {
public:
	RadioButton(std::string label, bool state=false, std::string address="");
	RadioButton(const RadioButton&) = delete;
	virtual ~RadioButton() {}
};
