#pragma once
#include <string>

#include "containers/container.h"

#include "events/event.h"

#include "geometry.h"


class TableBox: public Container {
public:
	TableBox(int columns, int rows, std::string address="");
	TableBox(const TableBox&) = delete;
	virtual ~TableBox();

	/* inherited from container class */
	virtual void _pack() override;
	virtual void handle_event(const Event& event) override;
	virtual int _handle_key(const int& key) override;
	virtual Dimension get_minimum_dimensions() override;

protected:
	int m_columns;
	int m_rows;
};
