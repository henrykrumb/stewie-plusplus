#pragma once
#include <string>

#include "evaluatable.h"

#include "widgets/widget.h"


class TextBox: public Widget, public Evaluatable {
public:
	TextBox(std::string label, std::string address="");
	TextBox(const TextBox&) = delete;
	virtual ~TextBox();
	
	virtual void handle_event(const Event& event);
	virtual int _handle_key(const int& key);
	virtual void _show(Canvas& canvas);
	
	virtual EvalVariant evaluate();

protected:
	bool m_empty;
	int m_cursor_x;
	int m_cursor_y;
	std::string m_label;
	std::string m_text;
};
