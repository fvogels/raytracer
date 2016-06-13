#include "scripting/objects/cons.h"
#include "scripting/objects/nil.h"
#include "scripting/objects/callable.h"
#include "scripting/environment.h"
#include <assert.h>

using namespace scripting;


scripting::Cons::Cons(std::shared_ptr<Object> car, std::shared_ptr<Object> cdr)
	: m_car(car), m_cdr(cdr)
{
	// NOP
}

bool scripting::Cons::operator==(const Object& other) const
{
	if (has_value_type<Cons>(other))
	{
		auto cons = value_cast<Cons>(other);

		return *m_car == *cons.car() && *m_cdr == *cons.cdr();
	}
	else
	{
		return false;
	}
}

void scripting::Cons::write(std::ostream& out) const
{
	out << "(" << m_car;

	std::shared_ptr<const Object> current = m_cdr;

	while (has_value_type<Cons>(current))
	{
		auto cons = std::static_pointer_cast<const Cons>(current);
		out << " " << cons->m_car;
		current = cons->m_cdr;
	}

	if (has_value_type<Nil>(current))
	{
		out << ")";
	}
	else
	{
		out << " . " << current << ")";
	}
}

std::shared_ptr<Object> scripting::Cons::evaluate(std::shared_ptr<scripting::Environment> environment)
{
	if (!is_list())
	{
		throw std::runtime_error("Evaluation expects well-formed list");
	}
	else
	{
		auto elts = elements();
		auto evaluated_head = elts[0]->evaluate(environment);

		std::vector<std::shared_ptr<Object>> argument_expressions(elts.begin() + 1, elts.end());

		return with_value_type<Callable, std::shared_ptr<Object>>(evaluated_head, [environment, &argument_expressions](std::shared_ptr<Callable> callable)
		{
			return callable->call(environment, argument_expressions);
		});
	}
}

std::shared_ptr<Object> scripting::Cons::car()
{
	return m_car;
}

std::shared_ptr<Object> scripting::Cons::cdr()
{
	return m_cdr;
}

bool scripting::Cons::is_list() const
{
	if (has_value_type<Cons>(m_cdr))
	{
		auto cdr = value_cast<Cons>(m_cdr);

		return cdr->is_list();
	}
	else return has_value_type<Nil>(m_cdr);
}

std::vector<std::shared_ptr<Object>> scripting::Cons::elements()
{
	assert(is_list());

	std::vector<std::shared_ptr<Object>> result;
	Cons* current = this;

	while (current != nullptr)
	{
		result.push_back(current->m_car);
		current = dynamic_cast<Cons*>(current->m_cdr.get());
	}

	return result;
}

std::shared_ptr<Object> scripting::construct_list(std::vector<std::shared_ptr<Object>> elements)
{
	std::shared_ptr<Object> result = std::make_shared<Nil>();

	for (auto it = elements.rbegin(); it != elements.rend(); ++it)
	{
		result = std::make_shared<Cons>(*it, result);
	}

	return result;
}