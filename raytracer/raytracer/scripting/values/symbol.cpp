#include "scripting/values/symbol.h"
#include "scripting/environment.h"

using namespace scripting;


scripting::Symbol::Symbol(const std::string& name)
	: m_name(name) { }

bool scripting::Symbol::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Symbol*>(&other);

	return that != nullptr && this->m_name == that->m_name;
}

void scripting::Symbol::write(std::ostream& out) const
{
	out << this->m_name;
}

std::shared_ptr<Object> scripting::Symbol::evaluate(std::shared_ptr<scripting::Environment> environment)
{
	return environment->lookup(*this);
}