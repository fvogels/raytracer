#include "scripting/objects/special-form.h"
#include "scripting/values.h"
#include "scripting/interpreter.h"
#include "scripting/environment.h"

using namespace scripting;


std::shared_ptr<Object> scripting::library::Let::call(std::shared_ptr<scripting::Environment> environment, std::shared_ptr<scripting::Heap> heap, const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() == 0)
	{
		throw std::runtime_error("let requires at least one argument");
	}
	else
	{
		auto bindings_argument = arguments[0];
		auto body_arguments = std::vector<std::shared_ptr<Object>>(arguments.begin() + 1, arguments.end());
		auto extended_environment = extend(environment);

		auto bindings_cons = value_cast<Cons>(bindings_argument);

		if (!bindings_cons->is_list())
		{
			throw std::runtime_error("Second argument of let must be well-formed list");
		}
		else
		{
			auto binding_list = bindings_cons->elements();

			for (auto binding_list_element : binding_list)
			{
				auto cons= value_cast<Cons>(binding_list_element);

				if (!cons->is_list())
				{
					throw std::runtime_error("Let expects list of pairs");
				}
				else
				{
					auto pair = cons->elements();

					if (pair.size() != 2)
					{
						throw std::runtime_error("Let expects list of pairs");
					}
					else
					{
						auto symbol = value_cast<Symbol>(pair[0]);
						auto value = pair[1]->evaluate(environment, heap);

						extended_environment->bind(*symbol, value);
					}
				}
			}

			std::shared_ptr<Object> last_result = std::make_shared<List>(std::vector<std::shared_ptr<Object>>());

			for (auto expr : body_arguments)
			{
				last_result = expr->evaluate(extended_environment, heap);
			}

			return last_result;
		}
	}
}

std::shared_ptr<Object> scripting::library::If::call(std::shared_ptr<scripting::Environment> environment, std::shared_ptr<scripting::Heap> heap, const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() != 2 && arguments.size() != 3)
	{
		throw std::runtime_error("if needs two or three arguments");
	}
	else
	{
		auto condition = value_cast<Boolean>(arguments[0]->evaluate(environment, heap));

		if (condition->value())
		{
			return arguments[1]->evaluate(environment, heap);
		}
		else
		{
			if (arguments.size() == 3)
			{
				return arguments[2]->evaluate(environment, heap);
			}
			else
			{
				return std::make_shared<Boolean>(false);
			}
		}
	}
}
