#include <iostream>
#include <map>
#include <queue>

#include "events/event.h"

#include "error.h"


Event::Event(
	const std::string& id,
	const std::string& source,
	const std::string& sink,
	const EventData& data):
		m_id(id),
		m_source(source),
		m_sink(sink),
		m_data(data)
{
}


Event::Event(const Event& event):
		m_id(event.m_id),
		m_source(event.m_source),
		m_sink(event.m_sink),
		m_data(event.m_data)
{
}


std::string Event::get_data_as_string() const {
	#ifdef __cpp_lib_any
	std::string s;
	
	try {
		s = std::any_cast<std::string>(m_data);
	} catch (const std::bad_any_cast& bac1) {
		try {
			s = std::string(
				std::any_cast<const char*>(m_data)
			);
		} catch (const std::bad_any_cast& bac2) {
			fatal("failed to convert event data to string");
		}
	}
	
	return s;
	#else
	return m_data;
	#endif
}
