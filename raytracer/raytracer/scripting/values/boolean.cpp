#include "scripting/values.h"

using namespace scripting;


scripting::Boolean::Boolean(bool b)
	: NativeValueAdapter<bool>(b)
{
	// NOP
}

std::shared_ptr<Object> scripting::Boolean::evaluate(std::shared_ptr<scripting::Environment>)
{
	return std::make_shared<Boolean>(m_value);
}