#pragma once

#include <string>

#include "events/event.h"

#include "canvas.h"
#include "geometry.h"

#include "containers/container.h"


class Frame: public Container {
public:
	Frame(std::string address="");
	Frame(const Frame&) = delete;
	virtual ~Frame() {}
	
	virtual bool _add_child(std::shared_ptr<Widget> widget);
	virtual void _pack();
	virtual int _handle_key(const int& c);

protected:
};
