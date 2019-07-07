#pragma once
#include "canvas.h"
#include "event.h"

#include "containers/container.h"


class VBox: public Container {
public:
	VBox(std::string address="");
	VBox(const VBox& vbox) = delete;
	~VBox();
	
	void _pack();
	int _handle_key(const int& key);

protected:
	
};
