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

	virtual bool add_child(std::shared_ptr<Widget> widget);
	virtual void pack();
	virtual int handle_key(int c);

protected:
};
