#include "scripting/values/native-functions.h"
#include "scripting/values/native-value-adapter.h"

using namespace scripting;


template<typename T>
void for_each(const std::vector<std::shared_ptr<Object>>& arguments, std::function<void(std::shared_ptr<T>)> function)
{
	for (auto argument : arguments)
	{
		with_value_type<Number, void>(argument, [&function](std::shared_ptr<T> converted)
		{
			function(converted);
		});
	}
}

std::shared_ptr<Object> scripting::library::Addition::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	double total = 0;

	for_each<Number>(arguments, [&total](std::shared_ptr<Number> number)
	{
		total += number->value();
	});

	return std::make_shared<Number>(total);
}

std::shared_ptr<Object> scripting::library::Subtraction::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	double result;

	if (arguments.size() == 0)
	{
		result = 0;
	}
	else if (arguments.size() == 1)
	{
		result = with_value_type<Number, double>(arguments[0], [&result](std::shared_ptr<Number> number)
		{
			return -number->value();
		});
	}
	else
	{
		result = with_value_type<Number, double>(arguments[0], [&result](std::shared_ptr<Number> number)
		{
			return number->value();
		});

		for (size_t i = 1; i < arguments.size(); ++i)
		{
			result -= with_value_type<Number, double>(arguments[i], [&result](std::shared_ptr<Number> number)
			{
				return number->value();
			});
		}
	}

	return std::make_shared<Number>(result);
}

std::shared_ptr<Object> scripting::library::Multiplication::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	double total = 1;

	for_each<Number>(arguments, [&total](std::shared_ptr<Number> number)
	{
		total *= number->value();
	});

	return std::make_shared<Number>(total);
}

std::shared_ptr<Object> scripting::library::Equality::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() == 0)
	{
		return std::make_shared<Boolean>(true);
	}
	else
	{
		for (size_t i = 1; i < arguments.size(); ++i)
		{
			if (*arguments[0] != *arguments[i])
			{
				return std::make_shared<Boolean>(false);
			}
		}

		return std::make_shared<Boolean>(true);
	}
}

std::shared_ptr<Object> scripting::library::Comparison::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() == 0)
	{
		return std::make_shared<Boolean>(true);
	}
	else
	{
		double last = value_cast<Number>(arguments[0])->value();

		for (size_t i = 1; i < arguments.size(); ++i)
		{
			double current = value_cast<Number>(arguments[i])->value();

			if (!compare(last, current))
			{
				return std::make_shared<Boolean>(false);
			}

			last = current;
		}

		return std::make_shared<Boolean>(true);
	}
}

bool scripting::library::LessThan::compare(double x, double y) const
{
	return x < y;
}

bool scripting::library::GreaterThan::compare(double x, double y) const
{
	return x > y;
}

bool scripting::library::NotLessThan::compare(double x, double y) const
{
	return x >= y;
}

bool scripting::library::NotGreaterThan::compare(double x, double y) const
{
	return x <= y;
}

std::shared_ptr<Object> scripting::library::Negation::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() != 1)
	{
		throw std::runtime_error("Negation expects exactly one argument");
	}
	else
	{
		auto argument = value_cast<Boolean>(arguments[0]);

		return std::make_shared<Boolean>(!argument->value());
	}
}
