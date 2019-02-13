#pragma once

#include "widget.h"


class Label: public Widget {
public:
	Label(std::string label, std::string address="");
	Label(const Label&) = delete;
	virtual ~Label();
};
