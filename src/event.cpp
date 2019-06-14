#include <map>
#include <queue>

#include "event.h"


static std::queue<Event> event_queue;
static std::map<std::string, EventNode*> event_nodes;


static void register_node(EventNode* node) {
	event_nodes.insert(
		std::pair<std::string, EventNode*>(
			node->get_address(), node
	));
}


static void unregister_node(EventNode* node) {
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
		
		/* no sink provided (broadcast) */
		if (sink.empty()) {
			for (auto it = event_nodes.begin(); it != event_nodes.end(); ++it) {
				it->second->handle_event(event);
				auto listeners = it->second->listeners;
				try {
					listeners.at(event.get_id())(event);
				} catch (std::exception e) {
					
				}
			}
		}
		else {
			EventNode* node = event_nodes.at(sink);
			node->handle_event(event);
			auto listeners = node->listeners;
			try {
				listeners.at(event.get_id())(event);
			} catch (std::exception e) {
				
			}
		}
	}
}



Event::Event(std::string id, std::string source, std::string sink):
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
	register_node(this);
}


EventNode::~EventNode() {
	unregister_node(this);
}


void EventNode::send_event(std::string id, std::string sink) {
	enqueue_event(Event(id, m_address, sink));
}

