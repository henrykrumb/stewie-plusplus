#include "../include/event.h"


EventNode::EventNode(std::string address):
		m_address(address)
{
	
}


EventNode::EventNode(const EventNode& e):
		m_address(e.m_address)
{
	
}
