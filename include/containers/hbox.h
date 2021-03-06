#pragma once
#include "containers/container.h"


class HBox: public Container {
public:
	HBox(std::string address="");
	HBox(const HBox&) = delete;
	virtual ~HBox();

	virtual void _pack();
	virtual int _handle_key(const int& key);
	
	virtual Dimension get_minimum_dimensions();

protected:
	
};
