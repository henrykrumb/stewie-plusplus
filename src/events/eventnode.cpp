#include <functional>
#include <memory>
#include <queue>
#include <string>

#include "events/event.h"
#include "events/eventnode.h"

#include "error.h"
#include "safequeue.h"


static SafeQueue<Event> event_queue;


int EventNode::s_instances = 0;
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
	event_queue.enqueue(event);
}


void enqueue_event(
		const std::string& id,
		const std::string& source,
		const std::string& sink,
		const EventData& data
) {
	event_queue.enqueue(Event(id, source, sink, data));
}


void dispatch_events() {
	/* copy event queue */
	while (!event_queue.empty()) {
		Event event = event_queue.dequeue();
		
		std::string sink = event.get_sink();
		
		/* no sink provided (broadcast) */
		if (sink.empty()) {
			for (auto it = event_nodes.begin(); it != event_nodes.end(); ++it) {
				if (!it->second->m_active) {
					continue;
				}
				// handle_event function
				it->second->handle_event(event);
				
				// call named listeners
				auto listener_map = it->second->m_listener_map;
				try {
					auto map_listeners = listener_map.at(event.get_id());
					for (auto& listener: map_listeners) {
						listener(event);
					}
				} catch (std::exception& e) {
					/* no listeners available */
				}
				
				// call unnamed listeners
				auto listeners = it->second->m_listeners;
				for (auto& listener: listeners) {
					listener(event);
				}
			}
		}
		/* sink provided (directed event) */
		else {
			try {
				auto node = event_nodes.at(sink);
				if (node->m_active) {
					// handle_event function
					node->handle_event(event);
					
					// call named listeners
					auto listener_map = node->m_listener_map;
					try {
						auto map_listeners = listener_map.at(event.get_id());
						for (auto& listener: map_listeners) {
							listener(event);
						}
					} catch (const std::out_of_range& e) {
						/* no listener available */
					}
					
					// call unnamed listeners
					auto listeners = node->m_listeners;
					for (auto& listener: listeners) {
						listener(event);
					}
				}
			} catch (const std::out_of_range& oor) {
				fatal("event sink " + sink + " not available");
			}
		}
	}
}


EventNode::EventNode(std::string address):
		m_address(address),
		m_active(true)
{
	++s_instances;
}


EventNode::~EventNode() {
}


void EventNode::add_listener(std::function<void(const Event&)> listener) {
	m_listeners.push_back(listener);
}


void EventNode::add_listener(std::string id, std::function<void(const Event&)> listener) {
	m_listener_map[id].push_back(listener);
}


void EventNode::send_event(
		const std::string& id,
		const std::string& sink,
		const EventData& data
) {
	enqueue_event(id, m_address, sink, data);
}
