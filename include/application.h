#pragma once

#include "frame.h"


class Application {
public:
	Application();
	Application(const Application& a) = delete;
	virtual ~Application() {}

	void run();

private:
	void p_exit();
	void p_exit_signal_handler();
	
	Frame m_frame;
};
