#include "scripting/values/object.h"

using namespace scripting;


void scripting::Number::accept(SExpressionVisitor& visitor) const
{
	visitor.visit(*this);
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