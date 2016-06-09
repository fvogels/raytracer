#include "scripting/values/native-functions.h"

using namespace scripting;


std::shared_ptr<const Object> scripting::library::Addition::perform(const std::vector<std::shared_ptr<const Object>>& arguments) const
{
	double total = 0;

	for (auto argument : arguments)
	{
		with_value_type<Number, void>(argument, [&total](std::shared_ptr<const Number> number)
		{
			total += number->value();
		});
	}

	return std::make_shared<Number>(total);
}