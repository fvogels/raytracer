#include "scripting/values.h"

using namespace scripting;


scripting::Number::Number(double value)
	: m_value(value) { }

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

std::shared_ptr<Object> scripting::Number::evaluate(std::shared_ptr<scripting::Environment>)
{
	return std::make_shared<Number>(this->m_value);
}