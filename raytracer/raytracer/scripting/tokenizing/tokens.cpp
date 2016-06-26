#include "tokens.h"

using namespace scripting;

void scripting::LeftParenthesisToken::accept(TokenVisitor& visitor) const
{
    visitor.visit(*this);
}

void scripting::RightParenthesisToken::accept(TokenVisitor& visitor) const
{
    visitor.visit(*this);
}

void scripting::SymbolToken::accept(TokenVisitor& visitor) const
{
    visitor.visit(*this);
}

void scripting::StringToken::accept(TokenVisitor& visitor) const
{
    visitor.visit(*this);
}

void scripting::NumberToken::accept(TokenVisitor& visitor) const
{
    visitor.visit(*this);
}