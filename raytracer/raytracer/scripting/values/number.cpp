#include "scripting/values.h"

using namespace scripting;


scripting::Number::Number(double value)
	: NativeValueAdapter<double>(value)
{
	// NOP
}

std::shared_ptr<Object> scripting::Number::evaluate(std::shared_ptr<scripting::Environment>)
{
	return std::make_shared<Number>(this->m_value);
}