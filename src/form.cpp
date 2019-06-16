#include "evaluatable.h"
#include "form.h"


Form::Form(std::string address):
		VBox(address)
{
	MAKE_ADDRESS(Form);
}


Form::~Form() {
	
}


std::map<std::string, EvalVariant> Form::evaluate(bool recursive) {
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
			std::shared_ptr<Form> form = std::dynamic_pointer_cast<Form>(*it);
			if (form != nullptr) {
				values.merge(form->evaluate(recursive));
			}
		}
	}
	
	return values;
}

