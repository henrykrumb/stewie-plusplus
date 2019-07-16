#pragma once
#include "containers/container.h"


class CentralBox: public Container {
public:
	CentralBox(std::string address="");
	CentralBox(const CentralBox&) = delete;
	CentralBox& operator=(const CentralBox&) = delete;
	virtual ~CentralBox();
	
	virtual bool _add_child(std::shared_ptr<Widget> widget);
	virtual void _pack();
	virtual int _handle_key(const int& c);
	
	virtual Dimension get_minimum_dimensions();

protected:
	
};
