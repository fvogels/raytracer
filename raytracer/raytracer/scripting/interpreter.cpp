#include "scripting/interpreter.h"
#include "scripting/Environment.h"

using namespace scripting;

std::shared_ptr<Object> scripting::evaluate(std::shared_ptr<Object> value, std::shared_ptr<Environment> environment)
{
	return value->evaluate(environment);
}