#include "scripting/s-expression.h"

using namespace scripting;

void scripting::List::accept(SExpressionVisitor& visitor) const
{
	visitor.visit(*this);
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

bool scripting::operator !=(const SExpression& a, const SExpression& b)
{
	return !(a == b);
}

bool scripting::Number::operator==(const SExpression& other) const
{
	auto that = dynamic_cast<const Number*>(&other);

	return that != nullptr && this->value == that->value;
}

bool scripting::Symbol::operator==(const SExpression& other) const
{
	auto that = dynamic_cast<const Symbol*>(&other);

	return that != nullptr && this->name == that->name;
}

bool scripting::String::operator==(const SExpression& other) const
{
	auto that = dynamic_cast<const String*>(&other);

	return that != nullptr && this->string == that->string;
}

bool scripting::List::operator==(const SExpression& other) const
{
	auto that = dynamic_cast<const List*>(&other);

	return that != nullptr && this->elements == that->elements;
}