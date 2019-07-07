#include <cmath>

#include "utils.h"

#include "widgets/label.h"


Label::Label(std::string label, std::string address):
		Widget(address),
		m_label(label)
{
	MAKE_ADDRESS(Label);
}


void Label::handle_event(const Event& event) {
	if (event.get_id() == LABEL_EVENT_I_SET_TEXT) {
		m_label = event.get_data_as_string();
	}
}


void Label::_show(Canvas& canvas) {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	
	Dimension d = stringsize(m_label);
	canvas.draw_text(
		m_label,
		x + roundi((float) (w - d.w()) / 2.0f),
		y + roundi((float) (h - d.h()) / 2.0f)
	);
}


int Label::_handle_key(const int& c) {
	return c;
}
