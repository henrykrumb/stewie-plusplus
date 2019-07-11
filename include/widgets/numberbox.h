#pragma once
#include <string>

#include "evaluatable.h"

#include "widgets/widget.h"


class NumberBox: public Widget, public Evaluatable {
public:
	NumberBox(std::string label, std::string address="");
	virtual ~NumberBox();
	
	virtual void handle_event(const Event& event);
	virtual int _handle_key(const int& key);
	virtual void _show(Canvas& canvas);
	
	virtual EvalVariant evaluate();

protected:
	bool m_empty;
	std::string m_label;
	std::string m_value;
	int m_cursor;
};
