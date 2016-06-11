#include "scripting/values/object.h"

using namespace scripting;

scripting::Object::Object()
{
	// NOP
}

bool scripting::operator !=(const Object& a, const Object& b)
{
	return !(a == b);
}

std::ostream& scripting::operator <<(std::ostream& out, const Object& object)
{
	object.write(out);

	return out;
}

std::shared_ptr<Object> scripting::Callable::evaluate(std::shared_ptr<scripting::Environment>)
{
	throw std::runtime_error("Cannot evaluate callable object");
}