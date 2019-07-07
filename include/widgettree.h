#pragma once
#include <memory>
#include <string>
#include <variant>

#include "container.h"
#include "widget.h"


typedef std::variant<
	bool,
	int,
	float,
	std::string
> ParameterVariant;

std::shared_ptr<Container> read_widgettree(const std::string& text);
