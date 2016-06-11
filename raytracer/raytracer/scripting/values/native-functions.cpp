#include "scripting/values/native-functions.h"

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

std::shared_ptr<Object> scripting::library::Multiplication::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	double total = 1;

	for_each<Number>(arguments, [&total](std::shared_ptr<Number> number)
	{
		total *= number->value();
	});

	return std::make_shared<Number>(total);
}