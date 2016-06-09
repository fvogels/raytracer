#include "scripting/values/object.h"

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

void scripting::Function::accept(SExpressionVisitor& visitor) const
{
	visitor.visit(*this);
}

bool scripting::operator !=(const Object& a, const Object& b)
{
	return !(a == b);
}

bool scripting::Number::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Number*>(&other);

	return that != nullptr && this->value == that->value;
}

bool scripting::Symbol::operator==(const Object& other) const
{
	auto that = dynamic_cast<const Symbol*>(&other);

	return that != nullptr && this->m_name == that->m_name;
}

bool scripting::String::operator==(const Object& other) const
{
	auto that = dynamic_cast<const String*>(&other);

	return that != nullptr && this->string == that->string;
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

void scripting::Symbol::write(std::ostream& out) const
{
	out << this->m_name;
}

void scripting::Number::write(std::ostream& out) const
{
	out << this->value;
}

void scripting::String::write(std::ostream& out) const
{
	out << '"' << this->string << '"';
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

std::ostream& scripting::operator <<(std::ostream& out, const Object& sexpr)
{
	sexpr.write(out);

	return out;
}