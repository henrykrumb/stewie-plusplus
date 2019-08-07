#include <cmath>

#include "error.h"
#include "utils.h"

#include "widgets/digit.h"


Digit::Digit(int value, std::string address):
		Widget(address),
		m_value(value)
{
	MAKE_ADDRESS(Digit);
}


void Digit::handle_event(const Event& event) {
	if (event.get_id() == DIGIT_EVENT_I_SET_VALUE) {
#ifdef __cpp_lib_any
		try {
			m_value = std::any_cast<int>(evet.get_data());
		}
#else
		m_value = std::stoi(event.get_data());
#endif
	}
}


void Digit::_show(Canvas& canvas) {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	
	// TODO prevent buffer overflow
	for (int row = 0; row < 5; ++row) {
		for (int col = 0; col < 5; ++col) {
			int dx = x + roundi((float) (w - 2) / 2.0f) + col;
			int dy = y + roundi((float) (h - 2) / 2.0f) + row;
			bool invert = glyphs[m_value - ' '][row] & (1 << (4 - col));
			canvas.draw_char(' ', dx, dy, invert);
		}
	}
}


int Digit::_handle_key(const int& c) {
	return c;
}


void Digit::set_value(const int& value) {
	/*if (value > 9 || value < 0) {
		fatal("digit value must be in range [0,9]");
	}*/
	m_value = value;
}
