#include "scripting/values/object.h"

using namespace scripting;


void scripting::Symbol::accept(SExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}

bool scripting::Symbol::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Symbol*>(&other);

	return that != nullptr && this->m_name == that->m_name;
}

void scripting::Symbol::write(std::ostream& out) const
{
	out << this->m_name;
}