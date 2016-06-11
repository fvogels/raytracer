#include "scripting/objects/macro.h"
#include "scripting/interpreter.h"
#include "scripting/environment.h"
#include <algorithm>

using namespace scripting;


std::shared_ptr<Object> scripting::Macro::call(std::shared_ptr<Environment> environment, const std::vector<std::shared_ptr<Object>>& argument_expressions) const
{
	return this->perform(argument_expressions)->evaluate(environment);
}
