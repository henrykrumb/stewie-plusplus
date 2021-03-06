#pragma once
#include "widgets/widget.h"


// TODO implement all glyphs until ~
#define DIGIT_GLYPH_MIN ' '
#define DIGIT_GLYPH_MAX 'Z'


const int glyphs[][5] = {
	{ // SPACE
		0, 0, 0, 0, 0
	},
	{ // !
		0b00100,
		0b00100,
		0b00100,
		0b00000,
		0b00100
	},
	{ // "
		0b01010,
		0b01010,
		0b00000,
		0b00000,
		0b00000
	},
	{ // #
		0b01010,
		0b11111,
		0b01010,
		0b11111,
		0b01010
	},
	{ // $
		0b00100,
		0b01110,
		0b10100,
		0b01110,
		0b00100
	},
	{ // %
		0b00001,
		0b10010,
		0b00100,
		0b01001,
		0b10000
	},
	{ // &
		0b11000,
		0b10010,
		0b11111,
		0b10010,
		0b11111
	},
	{ // '
		0b00100,
		0b00100,
		0b00000,
		0b00000,
		0b00000
	},
	{ // (
		0b00010,
		0b00100,
		0b00100,
		0b00100,
		0b00010
	},
	{ // )
		0b01000,
		0b00100,
		0b00100,
		0b00100,
		0b01000
	},
	{ // *
		0b00000,
		0b10101,
		0b01110,
		0b10101,
		0b00000
	},
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
		0b10101,
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
	},
	{ // :
		0b00000,
		0b00100,
		0b00000,
		0b00100,
		0b00000
	},
	{ // ;
		0b00000,
		0b00100,
		0b00000,
		0b00100,
		0b01000
	},
	{ // <
		0b00000,
		0b00110,
		0b11000,
		0b00110,
		0b00000
	},
	{ // =
		0b00000,
		0b01110,
		0b00000,
		0b01110,
		0b00000
	},
	{ // >
		0b00000,
		0b01100,
		0b00011,
		0b01100,
		0b00000
	},
	{ // ?
		0b01110,
		0b10001,
		0b00110,
		0b00000,
		0b00100
	},
  { // @
    0b01110,
    0b10001,
    0b10101,
    0b10011,
    0b01110
  },
  { // A
    0b01110,
    0b10001,
    0b11111,
    0b10001,
    0b10001
  },
  { // B
    0b11100,
    0b10010,
    0b11110,
    0b10001,
    0b11110,
  },
  { // C
    0b01111,
    0b10000,
    0b10000,
    0b10000,
    0b01111
  },
  { // D
    0b11110,
    0b10001,
    0b10001,
    0b10001,
    0b11110,
  },
  { // E
    0b11111,
    0b10000,
    0b11100,
    0b10000,
    0b11111,
  },
  { // F
    0b11111,
    0b10000,
    0b11100,
    0b10000,
    0b10000,
  },
  { // G
    0b01111,
    0b10000,
    0b10011,
    0b10001,
    0b01111
  },
  { // H
    0b10001,
    0b10001,
    0b11111,
    0b10001,
    0b10001
  },
  { // I
    0b01110,
    0b00100,
    0b00100,
    0b00100,
    0b01110
  },
  { // J
    0b11111,
    0b00001,
    0b00001,
    0b00001,
    0b11110
  },
  { // K
    0b10001,
    0b10010,
    0b11100,
    0b10010,
    0b10001
  },
  { // L
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b11111
  },
  { // M
    0b10001,
    0b11011,
    0b10101,
    0b10001,
    0b10001
  },
  { // N
    0b100001,
    0b110001,
    0b101001,
    0b100101,
    0b100011
  },
  { // O
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b01110
  },
  { // P
    0b11110,
    0b10001,
    0b11110,
    0b10000,
    0b10000
  },
  { // Q
    0b01110,
    0b10001,
    0b10101,
    0b10011,
    0b01111
  },
  { // R
    0b11110,
    0b10001,
    0b11110,
    0b10001,
    0b10001
  },
  { // S
    0b01111,
    0b10000,
    0b01110,
    0b00001,
    0b11110
  },
  { // T
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100
  },
  { // U
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b01110
  },
  { // V
    0b10001,
    0b10001,
    0b10001,
    0b01010,
    0b00100
  },
  { // W
    0b10001,
    0b10001,
    0b10001,
    0b10101,
    0b01010
  },
  { // X
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001
  },
  { // Y
    0b10001,
    0b01010,
    0b00100,
    0b00100,
    0b00100
  },
  { // Z
    0b11111,
    0b00010,
    0b00100,
    0b01000,
    0b11111
  },
  { // [
    0b01110,
    0b01000,
    0b01000,
    0b01000,
    0b01110
  },
  { // \
    0b10000,
    0b01000,
    0b00100,
    0b00010,
    0b00001
  },
  { // ]
    0b01110,
    0b00010,
    0b00010,
    0b00010,
    0b01110
  },
  { // ^
    0b00100,
    0b01010,
    0b00000,
    0b00000,
    0b00000
  },
  { // _
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b01110
  },
  { // `
    0b01000,
    0b00100,
    0b00000,
    0b00000,
    0b00000
  },
  { // a
    0b01110,
    0b00001,
    0b11111,
    0b10001,
    0b01111
  },
  { // b
    0b10000,
    0b10000,
    0b11110,
    0b10001,
    0b11110,
  },
  { // c
    0b00000,
    0b01111,
    0b10000,
    0b10000,
    0b01111
  },
  { // d
    0b00001,
    0b00001,
    0b01111,
    0b10001,
    0b01111,
  },
  { // e
    0b01110,
    0b10001,
    0b11111,
    0b10000,
    0b01111,
  },
  { // f
    0b00110,
    0b01000,
    0b11100,
    0b01000,
    0b01000,
  },
  { // g
    0b01111,
    0b10001,
    0b01111,
    0b00001,
    0b01110
  },
  { // h
    0b10000,
    0b10000,
    0b11110,
    0b10001,
    0b10001
  },
  { // i
    0b00100,
    0b00000,
    0b00100,
    0b00100,
    0b01110
  },
  { // j
    0b00010,
    0b00000,
    0b00010,
    0b00010,
    0b01100
  },
  { // k
    0b10000,
    0b10010,
    0b11100,
    0b10010,
    0b10010
  },
  { // l
    0b01000,
    0b01000,
    0b01000,
    0b01000,
    0b00110
  },
  { // m
    0b00000,
    0b11010,
    0b10101,
    0b10001,
    0b10001
  },
  { // n
    0b000000,
    0b111110,
    0b100001,
    0b100001,
    0b100001
  },
  { // o
    0b00000,
    0b01110,
    0b10001,
    0b10001,
    0b01110
  },
  { // p
    0b00000,
    0b11100,
    0b10010,
    0b11100,
    0b10000
  },
  { // q
    0b00000,
    0b01110,
    0b10010,
    0b01110,
    0b00010
  },
  { // r
    0b00000,
    0b00000,
    0b11110,
    0b10000,
    0b10000
  },
  { // s
    0b00000,
    0b00011,
    0b01100,
    0b00010,
    0b01100
  },
  { // t
    0b00100,
    0b00100,
    0b01110,
    0b00100,
    0b00100
  },
  { // u
    0b00000,
    0b00000,
    0b10001,
    0b10001,
    0b01110
  },
  { // v
    0b00000,
    0b00000,
    0b10001,
    0b01010,
    0b00100
  },
  { // w
    0b00000,
    0b00000,
    0b10001,
    0b10101,
    0b01010
  },
  { // x
    0b00000,
    0b00000,
    0b01010,
    0b00100,
    0b01010
  },
  { // y
    0b00000,
    0b10010,
    0b01010,
    0b00100,
    0b11000
  },
  { // z
    0b00000,
    0b11110,
    0b00100,
    0b01000,
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
