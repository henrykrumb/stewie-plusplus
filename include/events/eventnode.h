#pragma once
#include <atomic>
#include <memory>

#include "events/event.h"


class EventNode;

void register_node(std::shared_ptr<EventNode> node);
void unregister_node(std::shared_ptr<EventNode> node);

void enqueue_event(Event event);
void enqueue_event(
	const std::string& id,
	const std::string& source="",
	const std::string& sink="",
	const EventData& data="");
void dispatch_events();

class EventNode {
public:
	EventNode(std::string address);
	EventNode(const EventNode&) = delete;
	virtual ~EventNode();
	
	std::string get_address() const {
		return m_address;
	}
	
	void set_active(bool active) {
		m_active = active;
	}
	
	void add_listener(std::function<void(const Event&)> listener);
	void add_listener(std::string id, std::function<void(const Event&)> listener);
	void send_event(
		const std::string& id,
		const std::string& sink="",
		const EventData& data=""
	);
	virtual void handle_event(const Event& event) = 0;
	
	friend void dispatch_events();

protected:
	static int s_instances;
	
	std::atomic_bool m_active;
	std::string m_address;
	std::vector<std::function<void(const Event&)>> m_listeners;
	std::map<std::string, std::vector<std::function<void(const Event&)>>> m_listener_map;
};
