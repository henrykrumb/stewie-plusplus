#pragma once
#include <map>
#include <string>
#include <variant>
#include "vbox.h"


class Form: public VBox {
public:
	Form(std::string address="");
	Form(const Form& form) = delete;
	virtual ~Form();
	
	virtual bool _add_child(std::shared_ptr<Widget> child);
	std::map<std::string, eval_variant> evaluate();

protected:
};
