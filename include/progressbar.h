#pragma once

#include "widget.h"


class ProgressBar: public Widget {
public:
	ProgressBar(std::string address="");
	ProgressBar(const ProgressBar&) = delete;
	virtual ~ProgressBar();

	void set_progress(const float& progress);


protected:
	float m_progress;
};
