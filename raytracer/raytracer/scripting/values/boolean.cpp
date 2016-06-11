#include "scripting/values.h"

using namespace scripting;


scripting::Boolean::Boolean(bool value)
	: m_value(value) { }

bool scripting::Boolean::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Boolean*>(&other);

	return that != nullptr && this->m_value == that->m_value;
}

void scripting::Boolean::write(std::ostream& out) const
{
	out << this->m_value;
}

bool scripting::Boolean::value() const
{
	return m_value;
}

std::shared_ptr<Object> scripting::Boolean::evaluate(std::shared_ptr<scripting::Environment>)
{
	return std::make_shared<Boolean>(this->m_value);
}