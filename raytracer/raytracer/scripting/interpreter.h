#pragma once

#include "scripting/s-expression.h"
#include "scripting/environment.h"

namespace scripting
{
	std::shared_ptr<const SExpression> evaluate(std::shared_ptr<const SExpression> sexpr, std::shared_ptr<Environment> environment);
}