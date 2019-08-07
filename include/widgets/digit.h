#pragma once
#include "widgets/widget.h"


const int glyphs[][5] = {
	{ // +
		0b00000,
		0b00100,
		0b01110,
		0b00100,
		0b00000
	},
	{ // ,
		0b00000,
		0b00000,
		0b00000,
		0b00100,
		0b01000
	},
	{ // -
		0b00000,
		0b00000,
		0b01110,
		0b00000,
		0b00000
	},
	{ // .
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b01000
	},
	{ // /
		0b00001,
		0b00010,
		0b00100,
		0b01000,
		0b10000
	},
	{ // 0
		0b01110,
		0b10001,
		0b10001,
		0b10001,
		0b01110
	},
	{ // 1
		0b00110,
		0b00010,
		0b00010,
		0b00010,
		0b00010
	},
	{ // 2
		0b01110,
		0b10001,
		0b00010,
		0b00100,
		0b11111
	},
	{ // 3
		0b01110,
		0b00001,
		0b00110,
		0b00001,
		0b01110
	},
	{ // 4
		0b01001,
		0b10001,
		0b11111,
		0b00001,
		0b00001
	},
	{ // 5
		0b11111,
		0b10000,
		0b11110,
		0b00001,
		0b11110
	},
	{ // 6
		0b01111,
		0b10000,
		0b11111,
		0b10001,
		0b11111
	},
	{ // 7
		0b11111,
		0b00001,
		0b00010,
		0b00100,
		0b00100
	},
	{ // 8
		0b11110,
		0b10001,
		0b11111,
		0b10001,
		0b11111
	},
	{ // 9
		0b01111,
		0b10001,
		0b11111,
		0b00001,
		0b11110
	}
};


#define DIGIT_EVENT_I_SET_VALUE "set value"


class Digit: public Widget {
public:
	Digit(int value=0, std::string address="");
	Digit(const Digit&) = delete;
	virtual ~Digit() {}
	
	virtual void handle_event(const Event& event);
	
	virtual int _handle_key(const int& c);
	virtual void _show(Canvas& canvas);
	
	virtual void set_value(const int& value);
	virtual int get_value() const { return m_value; }

protected:
	int m_value;
};
