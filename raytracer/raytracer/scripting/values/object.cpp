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

void scripting::String::accept(SExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}

void scripting::Number::accept(SExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}

void scripting::Symbol::accept(SExpressionVisitor& visitor) const
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

bool scripting::Symbol::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Symbol*>(&other);

	return that != nullptr && this->m_name == that->m_name;
}

bool scripting::String::operator==(const Object& other) const
{
	auto that = dynamic_cast<const String*>(&other);

	return that != nullptr && this->string == that->string;
}


void scripting::Symbol::write(std::ostream& out) const
{
	out << this->m_name;
}

void scripting::Number::write(std::ostream& out) const
{
	out << this->value;
}

void scripting::String::write(std::ostream& out) const
{
	out << '"' << this->string << '"';
}

std::ostream& scripting::operator <<(std::ostream& out, const Object& sexpr)
{
	sexpr.write(out);

	return out;
}