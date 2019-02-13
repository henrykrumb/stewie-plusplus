#pragma once

#include "widget.h"


class ProgressBar: public Widget {
public:
	ProgressBar(std::string address="");
	ProgressBar(const ProgressBar&) = delete;
	virtual ~ProgressBar();
};
