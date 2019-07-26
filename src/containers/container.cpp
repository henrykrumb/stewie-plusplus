#include <algorithm>
#include <iostream>

#include "containers/container.h"


Container::Container(std::string address):
		Widget(address),
		m_focused_child(nullptr)
{
	m_focusable = true;
}


Container::~Container() {
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		(*it)->set_parent(nullptr);
	}
}


void Container::show(Canvas& canvas) {
	if (m_visible) {
		_show(canvas);
		for (auto it = m_children.begin(); it != m_children.end(); ++it) {
			(*it)->show(canvas);
		}
	}
}


/**
 * Usually, there is no need to display container widgets as they are used
 * to group visible widgets without being visible themselves.
 * So no need to be abstract.
 */
void Container::_show(Canvas& canvas) {}


int Container::handle_key(const int& c) {
	int key = c;
	if (m_focused_child != nullptr) {
		key = m_focused_child->handle_key(c);
	}
	return _handle_key(key);
}


bool Container::add_child(std::shared_ptr<Widget> widget) {
	if (_add_child(widget)) {
		widget->set_parent(this);
		m_children.push_back(widget);
		register_node(widget);
		pack();
		return true;
	}
	
	return false;
}


bool Container::remove_child(std::shared_ptr<Widget> widget) {
	if (_remove_child(widget)) {
		if (widget == m_focused_child) {
			m_focused_child = nullptr;
		}
		
		auto iter = std::find(m_children.begin(), m_children.end(), widget);
		if (iter == m_children.end()) {
			return false;
		}
		
		widget->set_parent(nullptr);
		m_children.erase(iter);
		pack();
		
		return true;
	}
	
	return false;
}


std::shared_ptr<Widget> Container::get_child(std::string address, bool recursive) {
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		if ((*it)->get_address() == address) {
			return *it;
		}
		
		if (recursive) {
			std::shared_ptr<Widget> child = (*it)->get_child(address, recursive);
			if (child != nullptr) {
				return child;
			}
		}
	}
	
	return nullptr;
}


void Container::pack() {
	_pack();
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		(*it)->pack();
	}
}


std::size_t Container::children() const {
	return m_children.size();
}


std::vector<std::shared_ptr<Widget>> Container::get_children() const {
	return m_children;
}


std::map<std::string, EvalVariant> Container::evaluate(bool recursive) {
	std::map<std::string, EvalVariant> values;
	
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		std::shared_ptr<Evaluatable> ev =
				std::dynamic_pointer_cast<Evaluatable>(*it);
		if (ev != nullptr) {
			std::string name = ev->get_name();
			values.insert(
				std::pair<std::string, EvalVariant>(name, ev->evaluate())
			);
		}
		
		if (recursive) {
			std::shared_ptr<Container> c = std::dynamic_pointer_cast<Container>(*it);
			if (c != nullptr) {
				#ifdef __cpp_lib_node_extract
				values.merge(c->evaluate(recursive));
				#else
				auto set = c->evaluate(recursive);
				for (auto jt = set.begin(); jt != set.end(); ++jt) {
					values.insert(*jt);
				}
				#endif
			}
		}
	}
	
	return values;
}


void Container::set_focus(const bool& focus) {
	m_focused = focus;
	if (focus) {
		focus_first();
	}
	else {
		for (auto it = m_children.begin(); it != m_children.end(); ++it) {
			(*it)->set_focus(false);
		}
	}
}


bool Container::focus_first() {
	if (m_children.empty()) {
		return false;
	}
	
	if (m_focused_child != nullptr) {
		m_focused_child->set_focus(false);
	}
	
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		if ((*it)->is_focusable()) {
			m_focused_child = *it;
			m_focused_child->set_focus(true);
			return true;
		}
	}
	
	return false;
}


bool Container::focus_next() {
	if (m_children.empty()) {
		return false;
	}
	
	auto focus_iter = std::find(
		m_children.begin(),
		m_children.end(),
		m_focused_child
	);
	
	if (focus_iter == m_children.end()) {
		return false;
	}
	
	while (true) {
		focus_iter++;
		
		if (focus_iter == m_children.end()) {
			return false;
		}
		
		if ((*focus_iter)->is_focusable()) {
			m_focused_child->set_focus(false);
			m_focused_child = *focus_iter;
			m_focused_child->set_focus(true);
			return true;
		}
	}
	
	return false;
}


bool Container::focus_previous() {
	if (m_children.empty()) {
		return false;
	}
	
	auto focus_iter = std::find(
		m_children.begin(),
		m_children.end(),
		m_focused_child
	);
	
	if (focus_iter == m_children.begin() || focus_iter == m_children.end()) {
		return false;
	}
	
	while (true) {
		focus_iter--;
		
		if ((*focus_iter)->is_focusable()) {
			m_focused_child->set_focus(false);
			m_focused_child = *focus_iter;
			m_focused_child->set_focus(true);
			return true;
		}
		
		if (focus_iter == m_children.begin()) {
			break;
		}
	}
	return false;
}


/**
 * Return the maximum minimum dimensions of all children and the container
 * widget itself.
 */
Dimension Container::get_minimum_dimensions() {
	int min_w = m_min_dimensions.w(), min_h = m_min_dimensions.h();
	
	for (auto& child: m_children) {
		auto child_dmin = child->get_minimum_dimensions();
		
		if (min_w < child_dmin.w()) {
			min_w = child_dmin.w();
		}
		
		if (min_h < child_dmin.h()) {
			min_h = child_dmin.h();
		}
	}
	
	return Dimension(min_w, min_h);
}


bool Container::is_focusable() const {
	for (auto& child: m_children) {
		if (child->is_focusable()) {
			return true;
		}
	}
}
