#pragma once
#include "containers/container.h"


class Banner: public Container {
public:
	Banner(std::string text, std::string address="");
	Banner(const Banner&) = delete;
	virtual ~Banner();
	
	virtual void _pack();
	virtual int _handle_key(const int& k);
	virtual Dimension get_minimum_dimensions();
	
	void set_text(const std::string& text);

protected:
	int m_digits;
	std::string m_text;
};
