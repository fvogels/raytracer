#include "scripting/objects/reference.h"
#include "scripting/objects/nil.h"

using namespace scripting;


scripting::ExternalReference::ExternalReference(std::shared_ptr<Object> location)
	: m_value( location )
{
	// NOP
}

bool scripting::ExternalReference::operator==(const Object& other) const
{
	auto that = dynamic_cast<const ExternalReference*>(&other);

	return m_value == that->m_value;
}

void scripting::ExternalReference::write(std::ostream& out) const
{
	out << "<REF>";
}

std::shared_ptr<Object> scripting::ExternalReference::evaluate(std::shared_ptr<scripting::Environment> environment)
{
	throw std::runtime_error("Cannot evaluate references");
}

std::shared_ptr<Object> scripting::ExternalReference::read() const
{
	return m_value;
}

void scripting::ExternalReference::write(std::shared_ptr<Object> value)
{
	m_value = value;
}

scripting::HeapReference::HeapReference()
	: ExternalReference(std::make_shared<Nil>())
{
	// NOP
}