/**
 * evaluatable.h - declaration of Evaluatable interface
 * 
 * Subclasses of this interface can be evaluated to a special variant type.
 * The Evaluatable interface is intended to be subclassed by Widgets, making
 * them earn the ability to be evaluated to a primitive value; e.g. CheckBox
 * widgets can be evaluated to booleans.
 * The idea here is that when a Form container (see form.cpp and form.h) is
 * finalized, all evaluatable widgets that belong to the Form are translated
 * to atomic values that are saved in a string-addressable hashmap.
 */

#pragma once
#include <string>
#include <variant>


typedef std::variant<bool, int, float, std::string> EvalVariant;


class Evaluatable {
public:
	Evaluatable(std::string name);
	virtual ~Evaluatable();
	
	std::string get_name() const;
	
	virtual EvalVariant evaluate() = 0;

protected:
	std::string m_name;
};
