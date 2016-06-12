#include "scripting/objects/nil.h"

using namespace scripting;


scripting::Nil::Nil()
{
	// NOP
}

bool scripting::Nil::operator==(const Object& other) const
{
	return has_value_type<Nil>(other);
}

void scripting::Nil::write(std::ostream& out) const
{
	out << "nil";
}

std::shared_ptr<Object> scripting::Nil::evaluate(std::shared_ptr<scripting::Environment>, std::shared_ptr<scripting::Heap>)
{
	throw std::runtime_error("Cannot evaluate nil");
}