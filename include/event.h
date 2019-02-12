#pragma once

#include <memory>
#include <string>
#include <vector>


class EventNode;


class Event {
public:
	Event(
		std::string id,
		std::shared_ptr<EventNode> source=nullptr,
		std::shared_ptr<EventNode> sink=nullptr
	);
	Event(const Event& event);
	virtual ~Event() {}

protected:
	std::string m_id;
	std::shared_ptr<EventNode> source;
	std::shared_ptr<EventNode> sink;
};



class EventNode {
public:
	EventNode(std::string address);
	EventNode(const EventNode& node);
	virtual ~EventNode() {}

protected:
	std::string m_address;
};



class EventManager {
public:
	EventManager();
	EventManager(const EventManager& manager) = delete;
	virtual ~EventManager() {}

private:
	std::vector<std::shared_ptr<EventNode>> m_nodes;
};
