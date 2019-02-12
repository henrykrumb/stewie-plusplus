#include <map>
#include <queue>

#include "../include/event.h"


Event::Event(std::string id,
	std::string source,
	std::string sink):
		m_id(id),
		m_source(source),
		m_sink(sink)
{
}


Event::Event(const Event& event):
		m_id(event.m_id),
		m_source(event.m_source),
		m_sink(event.m_sink)
{
}


EventNode::EventNode(std::string address):
		m_address(address)
{
	register_node(shared_from_this());
}


EventNode::~EventNode() {
	unregister_node(shared_from_this());
}


void EventNode::send_event(std::string id, std::string sink) {
	enqueue_event(Event(id, m_address, sink));
}


static std::queue<Event> event_queue;
static std::map<std::string, std::shared_ptr<EventNode>> event_nodes;


void register_node(std::shared_ptr<EventNode> node) {
	event_nodes.insert(
		std::pair<std::string, std::shared_ptr<EventNode>>(
			node->get_address(), node
	));
}


void unregister_node(std::shared_ptr<EventNode> node) {
	event_nodes.erase(node->get_address());
}


void enqueue_event(Event event) {
	event_queue.push(event);
}


void enqueue_event(std::string id, std::string source, std::string sink) {
	event_queue.push(Event(id, source, sink));
}


void dispatch_events() {
	while (!event_queue.empty()) {
		Event event = event_queue.front();
		event_queue.pop();
		
		std::string sink = event.get_sink();
		
		if (sink.empty()) {
			
		}
		else {
			std::shared_ptr<EventNode> node = event_nodes.at(sink);
			
		}
	}
}
