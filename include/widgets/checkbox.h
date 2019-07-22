#pragma once
#include <map>
#include <string>

#include "events/event.h"

#include "evaluatable.h"
#include "widget.h"


class CheckBox: public Widget, public Evaluatable {
public:
	CheckBox(
		std::string label,
		bool state=false,
		bool center=true,
		std::string address=""
	);
	CheckBox(const CheckBox&) = delete;
	virtual ~CheckBox() {}
	
	/** methods inherited from EventNode (Widget) **/
	virtual void handle_event(const Event& event);
	
	/** methods inherited from Widget **/
	virtual int _handle_key(const int& key);
	virtual void _show(Canvas& canvas);
	
	/** methods inherited from Evaluatable **/
	virtual EvalVariant evaluate();

protected:
	std::string m_label;
	bool m_state;
	bool m_center;
};
