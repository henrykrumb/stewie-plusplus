#include <map>
#include <queue>

#include "error.h"
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


void enqueue_event(
		std::string id,
		std::string source,
		std::string sink,
		EventVariant data
) {
	event_queue.push(Event(id, source, sink, data));
}


void dispatch_events() {
	/* copy event queue */
	std::queue<Event> queue = event_queue;
	while (!queue.empty()) {
		Event event = queue.front();
		queue.pop();
		event_queue.pop();
		
		std::string sink = event.get_sink();
		
		/* no sink provided (broadcast) */
		if (sink.empty()) {
			for (auto it = event_nodes.begin(); it != event_nodes.end(); ++it) {
				if (!it->second->m_active) {
					continue;
				}
				it->second->handle_event(event);
				auto listener_map = it->second->m_listener_map;
				try {
					auto listener = listener_map.at(event.get_id());
					listener(event);
				} catch (std::exception& e) {}
				auto listeners = it->second->m_listeners;
				for (auto jt = listeners.begin(); jt != listeners.end(); ++jt) {
					(*jt)(event);
				}
			}
		}
		else {
			// TODO handle exception :)
			EventNode* node = event_nodes.at(sink);
			if (node->m_active) {
				node->handle_event(event);
				auto listener_map = node->m_listener_map;
				try {
					auto listener = listener_map.at(event.get_id());
					listener(event);
				} catch (std::exception& e) {}
				auto listeners = node->m_listeners;
				for (auto it = listeners.begin(); it != listeners.end(); ++it) {
					(*it)(event);
				}
			}
		}
	}
}


Event::Event(
	std::string id,
	std::string source,
	std::string sink,
	EventVariant data):
		m_id(id),
		m_source(source),
		m_sink(sink),
		m_data(data)
{
}


Event::Event(const Event& event):
		m_id(event.m_id),
		m_source(event.m_source),
		m_sink(event.m_sink)
{
}


EventNode::EventNode(std::string address):
		m_address(address),
		m_active(true)
{
	register_node(this);
}


EventNode::~EventNode() {
	unregister_node(this);
}


void EventNode::add_listener(std::function<void(const Event&)> listener) {
	m_listeners.push_back(listener);
}


void EventNode::add_listener(std::string id, std::function<void(const Event&)> listener) {
	m_listener_map[id] = listener;
}


void EventNode::send_event(
		std::string id,
		std::string sink,
		EventVariant data
) {
	enqueue_event(Event(id, m_address, sink, data));
}

