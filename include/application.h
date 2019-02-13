#pragma once

#include "frame.h"


class Application {
public:
	Application();
	Application(const Application&) = delete;
	virtual ~Application() {}

	void run();

private:
	Frame m_frame;
};
