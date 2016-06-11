#include "scripting/values/string.h"

using namespace scripting;


scripting::String::String(const std::string& string)
	: m_value(string) { }

bool scripting::String::operator==(const Object& other) const
{
	auto that = dynamic_cast<const String*>(&other);

	return that != nullptr && this->m_value == that->m_value;
}

void scripting::String::write(std::ostream& out) const
{
	out << '"' << this->m_value << '"';
}

std::string scripting::String::value() const
{
	return this->m_value;
}

std::shared_ptr<Object> scripting::String::evaluate(std::shared_ptr<scripting::Environment>)
{
	return std::make_shared<String>(this->m_value);
}