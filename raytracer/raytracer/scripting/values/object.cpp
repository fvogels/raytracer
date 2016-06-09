#include "scripting/values/object.h"

using namespace scripting;

scripting::Object::Object(const Location& location)
	: m_location(location)
{
	// NOP
}

scripting::Object::Object()
	: m_location()
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