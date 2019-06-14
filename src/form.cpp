#include "evaluatable.h"
#include "form.h"


Form::Form(std::string address):
		VBox(address)
{

}


Form::~Form() {
	
}


bool Form::_add_child(std::shared_ptr<Widget> child) {
	if (std::dynamic_pointer_cast<Evaluatable>(child) != nullptr) {
		return true;
	}
	return false;
}


std::map<std::string, eval_variant> Form::evaluate() {
	std::map<std::string, eval_variant> values;
	
	for (auto it = m_children.begin(); it != m_children.end(); ++it) {
		std::shared_ptr<Evaluatable> ev =
				std::dynamic_pointer_cast<Evaluatable>(*it);
		std::string name = ev->get_name();
		values.insert(
				std::pair<std::string, eval_variant>(name, ev->evaluate())
		);
	}
	
	return values;
}

