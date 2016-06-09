#include "scripting/Environment.h"

using namespace scripting;

bool scripting::Environment::contains(const Symbol& symbol) const
{
	return m_bindings.find(symbol.name()) != m_bindings.end();
}

std::shared_ptr<const Object> scripting::Environment::lookup(const Symbol& symbol) const
{
	if (!contains(symbol))
	{
		throw std::runtime_error("Unknown symbol");
	}
	else
	{
		return m_bindings.at(symbol.name());
	}
}

void scripting::Environment::bind(const Symbol& symbol, std::shared_ptr<const Object> value)
{
	m_bindings[symbol.name()] = value;
}