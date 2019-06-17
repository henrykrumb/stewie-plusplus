#pragma once
#include "container.h"
#include "evaluatable.h"
#include "widget.h"


class RadioButton: public Widget, public Evaluatable {
public:
	RadioButton(std::string label, std::string address="");
	RadioButton(const RadioButton&) = delete;
	virtual ~RadioButton();
	
	void select();
	
	virtual void _show(Canvas& canvas);
	virtual int _handle_key(const int& key);
	
	virtual void handle_event(const Event& event);
	
	virtual EvalVariant evaluate();

protected:
	std::string m_label;
	bool m_state;
	bool m_center;
};
