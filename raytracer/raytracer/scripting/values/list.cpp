#include "scripting/values/object.h"

using namespace scripting;


scripting::List::List(const Location& location, const std::vector<std::shared_ptr<const Object>>& elements)
	: Object(location), m_elements(elements) 
{
	// NOP
}

scripting::List::List(const std::vector<std::shared_ptr<const Object>>& elements)
	: m_elements(elements) 
{ 
	// NOP
}

void scripting::List::accept(ObjectVisitor& visitor) const
{
	visitor.visit(*this);
}

bool scripting::List::operator==(const Object& other) const
{
	auto that = dynamic_cast<const List*>(&other);

	if (that != nullptr)
	{
		if (this->m_elements.size() == that->m_elements.size())
		{
			for (size_t i = 0; i != this->m_elements.size(); ++i)
			{
				auto& x = *this->m_elements[i];
				auto& y = *that->m_elements[i];

				if (x != y)
				{
					return false;
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void scripting::List::write(std::ostream& out) const
{
	bool first = true;

	out << '(';

	for (auto& element : this->m_elements)
	{
		if (first)
		{
			first = false;
		}
		else
		{
			out << ' ';
		}

		element->write(out);
	}

	out << ')';
}

size_t scripting::List::size() const 
{
	return m_elements.size(); 
}

std::shared_ptr<const Object> scripting::List::nth_element(size_t index) const 
{
	return m_elements[index]; 
}