#include "scripting/values/object.h"

using namespace scripting;


scripting::String::String(const std::string& string)
	: string(string) { }

void scripting::String::accept(ObjectVisitor& visitor) const
{
	visitor.visit(*this);
}

bool scripting::String::operator==(const Object& other) const
{
	auto that = dynamic_cast<const String*>(&other);

	return that != nullptr && this->string == that->string;
}

void scripting::String::write(std::ostream& out) const
{
	out << '"' << this->string << '"';
}

std::string scripting::String::value() const
{
	return this->string;
}

std::shared_ptr<Object> scripting::String::evaluate(std::shared_ptr<scripting::Environment>)
{
	return std::make_shared<String>(this->string);
}