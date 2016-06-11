#include "scripting/objects/function.h"
#include "scripting/interpreter.h"
#include "scripting/environment.h"
#include <algorithm>

using namespace scripting;


std::shared_ptr<Object> scripting::Function::call(std::shared_ptr<Environment> environment, std::shared_ptr<scripting::Heap> heap, const std::vector<std::shared_ptr<Object>>& argument_expressions) const
{
	std::vector<std::shared_ptr<Object>> argument_values;
	argument_values.resize(argument_expressions.size());

	std::transform(argument_expressions.begin(), argument_expressions.end(), argument_values.begin(), [environment, heap](std::shared_ptr<Object> expr) {
		return ::evaluate(expr, environment, heap);
	});

	return this->perform(heap, argument_values);
}
