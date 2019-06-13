#include "progressbar.h"


ProgressBar::ProgressBar(std::string address):
		Widget(address)
{
	MAKE_ADDRESS(ProgressBar);
	m_focusable = false;
}


ProgressBar::~ProgressBar() {
	
}


void ProgressBar::set_progress(const float& progress) {
	if (progress < 0.0f || progress > 1.0f) {
		throw std::invalid_argument("invalid progress value");
	}
	m_progress = progress;
}
