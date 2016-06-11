#include "scripting/values.h"

using namespace scripting;


std::shared_ptr<Object> scripting::Boolean::evaluate(std::shared_ptr<scripting::Environment>)
{
	return std::make_shared<Boolean>(m_value);
}