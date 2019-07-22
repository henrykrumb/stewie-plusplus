#pragma once

#include "canvas.h"

#include "containers/container.h"

#include "events/event.h"


class VBox: public Container {
public:
	VBox(std::string address="");
	VBox(const VBox& vbox) = delete;
	~VBox();
	
	virtual void _pack();
	virtual int _handle_key(const int& key);
	
	virtual Dimension get_minimum_dimensions();

protected:
	
};
