#pragma once
 
#ifdef __cpp_lib_any
#include <any>
#endif

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>


/*
 * Macro to generate default EventNode addresses.
 * Use this in subclass constructors to obtain concise
 * address strings (e.g. ProgressBar::12).
 */
#define MAKE_ADDRESS(x) \
	m_address = address.empty() ? #x "::" + std::to_string(s_instances) : address

#ifdef __cpp_lib_any
typedef std::any EventData;
#else
typedef std::string EventData;
#endif


class Event {
public:
	Event(
		const std::string& id,
		const std::string& source,
		const std::string& sink="",
		const EventData& data=""
	);
	Event(const Event& event);
	virtual ~Event() {}

	std::string get_id() const { return m_id; }
	std::string get_source() const { return m_source; }
	std::string get_sink() const { return m_sink; }
	EventData get_data() const { return m_data; }
	std::string get_data_as_string() const;

protected:
	std::string m_id;
	std::string m_source;
	std::string m_sink;
	EventData m_data;
};


