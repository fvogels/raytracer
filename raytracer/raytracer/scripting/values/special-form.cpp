#include "scripting/values/special-form.h"
#include "scripting/values.h"
#include "scripting/interpreter.h"
#include "scripting/environment.h"

using namespace scripting;


std::shared_ptr<Object> scripting::library::Let::call(std::shared_ptr<scripting::Environment> environment, const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() == 0)
	{
		throw std::runtime_error("let requires at least one argument");
	}
	else
	{
		auto bindings = arguments[0];
		auto body = std::vector<std::shared_ptr<Object>>(arguments.begin() + 1, arguments.end());
		auto extended_environment = extend(environment);

		with_value_type<List, void>(bindings, [environment, extended_environment](std::shared_ptr<List> binding_list)
		{
			for (auto binding_pair : binding_list->elements())
			{
				with_value_type<List, void>(binding_pair, [environment, extended_environment](std::shared_ptr<List> pair)
				{
					if (pair->elements().size() != 2)
					{
						throw std::runtime_error("Let expects pairs");
					}
					else
					{
						auto value = pair->elements()[1]->evaluate(environment);

						with_value_type<Symbol, void>(pair->elements()[0], [extended_environment, value](std::shared_ptr<Symbol> symbol)
						{
							extended_environment->bind(*symbol, value);
						});
					}
				});
			}
		});

		std::shared_ptr<Object> last_result = std::make_shared<List>(std::vector<std::shared_ptr<Object>>());

		for (auto expr : body)
		{
			last_result = expr->evaluate(extended_environment);
		}

		return last_result;
	}
}

std::shared_ptr<Object> scripting::library::If::call(std::shared_ptr<scripting::Environment> environment, const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() != 2 && arguments.size() != 3)
	{
		throw std::runtime_error("if needs two or three arguments");
	}
	else
	{
		auto condition = value_cast<Boolean>(arguments[0]->evaluate(environment));

		if (condition->value())
		{
			return arguments[1]->evaluate(environment);
		}
		else
		{
			if (arguments.size() == 3)
			{
				return arguments[2]->evaluate(environment);
			}
			else
			{
				return std::make_shared<Boolean>(false);
			}
		}
	}
}
