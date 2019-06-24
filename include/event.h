#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <variant>


typedef std::variant<int, float, long, std::string> EventVariant;

class EventNode;

void register_node(EventNode* node);
void unregister_node(EventNode* node);

class Event {
public:
	Event(
			std::string id,
			std::string source,
			std::string sink="",
			EventVariant data=""
	);
	Event(const Event& event);
	virtual ~Event() {}

	std::string get_id() const { return m_id; }
	std::string get_source() const { return m_source; }
	std::string get_sink() const { return m_sink; }
	EventVariant get_data() const { return m_data; }

protected:
	std::string m_id;
	std::string m_source;
	std::string m_sink;
	EventVariant m_data;
};


void enqueue_event(Event event);
void enqueue_event(std::string id, std::string source="", std::string sink="", EventVariant data="");
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
	void send_event(std::string id, std::string sink="", EventVariant data="");
	virtual void handle_event(const Event& event) = 0;
	
	friend void dispatch_events();

protected:
	bool m_active;
	std::string m_address;
	std::vector<std::function<void(const Event&)>> m_listeners;
	std::map<std::string, std::vector<std::function<void(const Event&)>>> m_listener_map;
};
