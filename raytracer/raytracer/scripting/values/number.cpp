#include "scripting/values/object.h"

using namespace scripting;


scripting::Number::Number(double value)
	: m_value(value) { }

void scripting::Number::accept(ObjectVisitor& visitor) const
{
	visitor.visit(*this);
}

bool scripting::Number::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Number*>(&other);

	return that != nullptr && this->m_value == that->m_value;
}

void scripting::Number::write(std::ostream& out) const
{
	out << this->m_value;
}

double scripting::Number::value() const
{
	return m_value;
}