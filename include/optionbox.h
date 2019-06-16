#pragma once
#include "evaluatable.h"
#include "widget.h"


#define EVENT_OPTIONBOX_ACTIVATE "optionbox.activate"
#define EVENT_OPTIONBOX_NEXT "optionbox.next"
#define EVENT_OPTIONBOX_PREVIOUS "optionbox.previous"


class OptionBox: public Widget, public Evaluatable {
public:
	OptionBox(std::string label, std::vector<std::string> options, std::string address="");
	OptionBox(const OptionBox&) = delete;
	virtual ~OptionBox();
	
	/** methods inherited from EventNode (Widget) **/
	virtual void handle_event(const Event& event);
	
	/** methods inherited from Widget **/
	virtual int _handle_key(const int& c);
	virtual void _show(Canvas& canvas);
	
	/** methods inherited from Evaluatable **/
	virtual EvalVariant evaluate();

protected:
	bool m_center;
	std::string m_label;
	std::vector<std::string> m_options;
	std::vector<std::string>::iterator m_option_iter;
};
