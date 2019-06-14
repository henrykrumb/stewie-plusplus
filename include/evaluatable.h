#pragma once
#include <string>
#include <variant>


typedef std::variant<bool, int, float, std::string> eval_variant;


class Evaluatable {
public:
	Evaluatable(std::string name);
	virtual ~Evaluatable();
	
	std::string get_name() const;
	
	virtual eval_variant evaluate() = 0;

protected:
	std::string m_name;
};
