#pragma once

#include "scripting/values/s-expression.h"
#include "scripting/environment.h"

namespace scripting
{
	std::shared_ptr<const Object> evaluate(std::shared_ptr<const Object> sexpr, std::shared_ptr<Environment> environment);
}