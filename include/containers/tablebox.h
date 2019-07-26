#pragma once


class TableBox: public Container {
public:
	TableBox(int columns, int rows);
	TableBox(const TableBox&) = delete;
	virtual ~TableBox();

	/* inherited from container class */
	virtual void _pack() override;
	virtual void handle_event(const Event& event) override;
	virtual void _handle_key(const int& key) override;
	virtual Dimension get_minimum_dimensions() override;

protected:
	int m_columns;
	int m_rows;
};
