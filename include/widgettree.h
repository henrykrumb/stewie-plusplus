#pragma once
#include <memory>
#include <string>
#include <variant>

#include "containers/container.h"

#include "widgets/widget.h"


std::shared_ptr<Container> read_widgettree(std::string json);
