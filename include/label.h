#pragma once

#include "widget.h"


class Label: public Widget {
public:
	Label(std::string label, std::string address="");
	Label(const Label&) = delete;
	virtual ~Label() {}
	
	virtual int _handle_key(const int& c);
	virtual void _show(Canvas& canvas);

protected:
	std::string m_label;
};
