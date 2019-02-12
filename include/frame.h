#pragma once

#include <string>

#include "canvas.h"
#include "container.h"
#include "geometry.h"


class Frame: public Container {
public:
	Frame(Box box, std::string address="");
	Frame(const Frame& frame);
	virtual ~Frame() {}

	virtual int i_handle_key(int c);

protected:
};
