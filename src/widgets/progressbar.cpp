#include <cmath>
#include <iomanip>
#include <sstream>

#include "error.h"
#include "utils.h"

#include "widgets/progressbar.h"


ProgressBar::ProgressBar(std::string label, std::string address):
		Widget(address),
		Evaluatable(label),
		m_label(label),
		m_progress(0.0f)
{
	MAKE_ADDRESS(ProgressBar);
	if (m_name.empty()) {
		m_name = m_address;
	}
	m_focusable = false;
}


ProgressBar::~ProgressBar() {
	
}


void ProgressBar::set_progress(const float& progress) {
	if (progress < 0.0f || progress > 1.0f) {
		throw std::invalid_argument("invalid progress value");
	}
	m_progress = progress;
}


void ProgressBar::handle_event(const Event& event) {
	if (event.get_id() == PROGRESSBAR_I_EVENT_SET_PROGRESS) {
		#ifdef __cpp_lib_any
			try {
				set_progress(std::any_cast<float>(event.get_data()));
			} catch (const std::bad_any_cast& bac) {
				fatal("tried to set ProgressBar value with wrong datatype");
			}
		#else
				float progress = std::stof(event.get_data(), nullptr);
		#endif
	}
	else {
		
	}
}


void ProgressBar::_show(Canvas& canvas) {
	int x = m_box.x(), y = m_box.y(), w = m_box.w(), h = m_box.h();
	
	std::stringstream sstr;
	
	int percentage = (int) (100.0f * m_progress);
	int w_total = (int)(w / 2.0f - 2.0f);
	int w_full = (int)((float) w_total * m_progress);
	int w_empty = (int)((float) w_total * (1.0f - m_progress));
	
	sstr << "[";
	for (int i = 0; i < w_full; i++) {
		sstr << "=";
	}
	for (int i = 0; i < w_empty; i++) {
		sstr << " ";
	}
	sstr << "] " << std::setw(3) << percentage << "%";
	std::string text = sstr.str();
	
	Dimension d = stringsize(text);
	canvas.draw_text(
		text,
		x + roundi((float) (w - d.w()) / 2.0f),
		y + roundi((float) (h - d.h()) / 2.0f)
	);
}


int ProgressBar::_handle_key(const int& key) {
	return key;
}


EvalVariant ProgressBar::evaluate() {
	#ifdef __cpp_lib_variant
	return EvalVariant(m_progress);
	#else
	return EvalVariant(std::to_string(m_progress));
	#endif
}
