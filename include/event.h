#pragma once

#include <memory>
#include <string>
#include <variant>

typedef std::variant<int, float, long, std::string> EventVariant;


class EventNode;


class Event {
public:
	Event(std::string id, std::string source, std::string sink="");
	Event(const Event& event);
	virtual ~Event() {}

	std::string get_id() const { return m_id; }
	std::string get_source() const { return m_source; }
	std::string get_sink() const { return m_sink; }

protected:
	std::string m_id;
	std::string m_source;
	std::string m_sink;
};



class EventNode {
public:
	EventNode(std::string address);
	EventNode(const EventNode& node) = delete;
	virtual ~EventNode();

	std::string get_address() const {
		return m_address;
	}

	void send_event(std::string id, std::string sink="");

protected:
	std::string m_address;
};


void enqueue_event(Event event);
void enqueue_event(std::string id, std::string sink="");
void dispatch_events();
