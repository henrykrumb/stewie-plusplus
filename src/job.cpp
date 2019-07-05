#include "job.h"


Job::Job(
	JobFunction run,
	std::shared_ptr<ProgressBar> progressbar,
	std::string address
):
	EventNode(address),
	m_running(false),
	m_status(JOB_STATUS_NONE),
	m_run(run),
	m_progressbar(progressbar)
{
	MAKE_ADDRESS(Job);
	
	m_thread = nullptr;
}


Job::~Job() {
	kill();
}


void Job::handle_event(const Event& event) {
	if (event.get_id() == JOB_EVENT_I_START) {
		start();
	}
	else if (event.get_id() == JOB_EVENT_I_RESTART) {
		restart();
	}
	else if (event.get_id() == JOB_EVENT_I_KILL) {
		kill();
	}
	else if (event.get_id() == JOB_EVENT_I_JOIN) {
		if (m_status == JOB_STATUS_NONE) {
			if (m_thread) {
				m_thread->join();
			}
			m_thread = nullptr;
		}
	}
}


void Job::start() {
	switch (m_status) {
		case JOB_STATUS_NONE:
			m_status = JOB_STATUS_RUNNING;
			m_running = true;
			m_thread = std::make_shared<std::thread>([=] {
				m_run(*this);
				m_running = false;
				
				if (m_status == JOB_STATUS_RUNNING) {
					m_status = JOB_STATUS_NONE;
				}
				
				this->send_event(JOB_EVENT_I_JOIN, m_address);
			});
			break;
		case JOB_STATUS_RUNNING:
			throw std::runtime_error("job is already running");
		case JOB_STATUS_ERROR:
			throw std::runtime_error("trying to run job that already failed");
		default:
			throw std::runtime_error("illegal job status");
	}
}


void Job::restart() {
	kill();
	start();
}


void Job::kill() {
	m_running = false;
	
	if (m_thread) {
		m_thread->join();
	}
	
	m_thread = nullptr;
}


JobStatus Job::get_status() const {
	return m_status;
}


/*
 * This method is intended to be called from within the Job function
 * to update the associated ProgressBar's value.
 */
void Job::set_progress(float progress) {
	if (!m_progressbar) {
		return;
	}
	if (progress < 0.0f || progress > 1.0f) {
		throw std::invalid_argument("invalid progress value");
	}
	m_progressbar->set_progress(progress);
}


/*
 * This method should be called from within every Job function to query
 * whether the Job is still running. This way we can control Job
 * functions which enables us to kill Jobs from other threads.
 */
bool Job::is_running() {
	return m_running;
}
