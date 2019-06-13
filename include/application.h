#pragma once

#include <memory>
#include <vector>

#include "frame.h"


class Application {
public:
	Application();
	Application(const Application&) = delete;
	virtual ~Application() {}
	
	void add_frame(std::shared_ptr<Frame> frame);
	void run();

private:
	std::vector<std::shared_ptr<Frame>> m_frames;
};
