#include "evaluatable.h"


Evaluatable::Evaluatable(std::string name):
		m_name(name)
{
	
}


Evaluatable::~Evaluatable() {
	
}


std::string Evaluatable::get_name() const {
	return m_name;
}
