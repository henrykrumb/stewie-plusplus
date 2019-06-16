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
	
	std::map<std::string, EvalVariant> evaluate(bool recursive=true);

protected:
};
