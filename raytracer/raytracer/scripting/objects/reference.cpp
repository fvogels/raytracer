#include "scripting/objects/reference.h"
#include "scripting/objects/nil.h"

using namespace scripting;


scripting::HeapReference::HeapReference()
	: m_value( std::make_shared<Nil>() )
{
	// NOP
}

bool scripting::HeapReference::operator==(const Object& other) const
{
	auto that = dynamic_cast<const HeapReference*>(&other);

	return this == &other;
}

void scripting::HeapReference::write(std::ostream& out) const
{
	out << "<HEAP-REF>";
}

std::shared_ptr<Object> scripting::HeapReference::evaluate(std::shared_ptr<scripting::Environment> environment)
{
	throw std::runtime_error("Cannot evaluate references");
}

std::shared_ptr<Object> scripting::HeapReference::read() const
{
	return m_value;
}

void scripting::HeapReference::write(std::shared_ptr<Object> value)
{
	m_value = value;
}