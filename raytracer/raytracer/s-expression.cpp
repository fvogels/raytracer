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