#pragma once
#include "evaluatable.h"
#include "widget.h"


#define PROGRESSBAR_I_EVENT_SET_PROGRESS "set progress"


class ProgressBar: public Widget, public Evaluatable {
public:
	ProgressBar(std::string label, std::string address="");
	ProgressBar(const ProgressBar&) = delete;
	virtual ~ProgressBar();
	
	void set_progress(const float& progress);
	
	virtual void handle_event(const Event& event);
	
	virtual void _show(Canvas& canvas);
	virtual int _handle_key(const int& key);
	
	virtual EvalVariant evaluate();


protected:
	std::string m_label;
	float m_progress;
};
