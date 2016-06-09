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

void scripting::Number::accept(SExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}

void scripting::Function::accept(SExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}

bool scripting::operator !=(const Object& a, const Object& b)
{
	return !(a == b);
}

bool scripting::Number::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Number*>(&other);

	return that != nullptr && this->value == that->value;
}

void scripting::Number::write(std::ostream& out) const
{
	out << this->value;
}

std::ostream& scripting::operator <<(std::ostream& out, const Object& sexpr)
{
	sexpr.write(out);

	return out;
}