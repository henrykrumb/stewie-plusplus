#pragma once
#include <atomic>
#include <functional>
#include <thread>

#include "event.h"
#include "progressbar.h"


#define JOB_EVENT_O_FINISH "finish"
#define JOB_EVENT_O_TERMINATE "terminate"
#define JOB_EVENT_O_ERROR "error"

#define JOB_EVENT_I_START "start"
#define JOB_EVENT_I_RESTART "restart"
#define JOB_EVENT_I_JOIN "join"
#define JOB_EVENT_I_KILL "kill"


enum JobStatus {
	JOB_STATUS_NONE,
	JOB_STATUS_RUNNING,
	JOB_STATUS_ERROR
};


class Job;
typedef std::function<void(Job& j)> JobFunction;


class Job: public EventNode {
public:
	Job(
		JobFunction run,
		std::shared_ptr<ProgressBar> progressbar=nullptr,
		std::string address=""
	);
	Job(const Job& job) = delete;
	virtual ~Job();
	
	virtual void handle_event(const Event& event);
	
	void start();
	void restart();
	void kill();
	
	JobStatus get_status() const;
	void set_progress(float progress);
	bool is_running();

protected:
	bool m_running;
	JobStatus m_status;
	JobFunction m_run;
	std::shared_ptr<ProgressBar> m_progressbar;
	std::shared_ptr<std::thread> m_thread;
};
