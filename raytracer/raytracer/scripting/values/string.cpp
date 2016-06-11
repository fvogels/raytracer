#include "scripting/values/string.h"

using namespace scripting;


std::shared_ptr<Object> scripting::String::evaluate(std::shared_ptr<scripting::Environment>)
{
	return std::make_shared<String>(this->m_value);
}