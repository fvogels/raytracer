#include "scripting/values/object.h"

using namespace scripting;


scripting::List::List(const std::vector<std::shared_ptr<Object>>& elements)
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

std::shared_ptr<Object> scripting::List::evaluate(std::shared_ptr<scripting::Environment> environment)
{
	if (m_elements.size() == 0)
	{
		return std::make_shared<List>(std::vector<std::shared_ptr<Object>>());
	}
	else
	{
		auto evaluated_head = m_elements[0]->evaluate(environment);

		std::vector<std::shared_ptr<Object>> argument_expressions;
		for (size_t i = 1; i < m_elements.size(); ++i)
		{
			argument_expressions.push_back(m_elements[i]);
		}

		return with_value_type<Callable, std::shared_ptr<Object>>(evaluated_head, [environment, &argument_expressions](std::shared_ptr<Callable> callable)
		{
			return callable->call(environment, argument_expressions);
		});
	}
}