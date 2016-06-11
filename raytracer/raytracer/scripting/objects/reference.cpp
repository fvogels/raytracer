#include "scripting/objects/reference.h"

using namespace scripting;


scripting::Reference::Reference(unsigned id)
	: m_id(id) { }

bool scripting::Reference::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Reference*>(&other);

	return that != nullptr && this->m_id == that->m_id;
}

void scripting::Reference::write(std::ostream& out) const
{
	out << "REF[" << m_id << "]";
}

std::shared_ptr<Object> scripting::Reference::evaluate(std::shared_ptr<scripting::Environment> environment, std::shared_ptr<scripting::Heap>)
{
	throw std::runtime_error("Cannot evaluate references");
}