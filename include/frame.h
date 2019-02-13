#pragma once

#include <string>

#include "canvas.h"
#include "container.h"
#include "geometry.h"


class Frame: public Container {
public:
	Frame(std::string address="");
	Frame(const Frame&) = delete;
	virtual ~Frame() {}

	virtual void pack();
	virtual int handle_key(int c);

protected:
};
