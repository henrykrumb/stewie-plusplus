#pragma once
#include <string>

#include "evaluatable.h"

#include "widgets/widget.h"


#define NUMBERBOX_EVENT_I_SET_VALUE "set value"


class NumberBox: public Widget, public Evaluatable {
public:
	NumberBox(std::string label, std::string address="");
	NumberBox(const NumberBox&) = delete;
	virtual ~NumberBox();
	
	virtual void handle_event(const Event& event);
	virtual int _handle_key(const int& key);
	virtual void _show(Canvas& canvas);
	
	virtual float get_value();
	virtual void set_value(float f);
	
	virtual void allow_negative(bool an);
	virtual void allow_float(bool af);
	
	virtual EvalVariant evaluate();

protected:
	bool m_empty;
	std::string m_label;
	std::string m_value;
	int m_cursor;
	bool m_allow_negative;
	bool m_allow_float;
};
