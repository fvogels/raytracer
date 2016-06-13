#include "scripting/objects/native-functions.h"
#include "scripting/objects/native-object.h"
#include "scripting/objects.h"

using namespace scripting;


template<typename T>
void for_each(const std::vector<std::shared_ptr<Object>>& arguments, std::function<void(std::shared_ptr<T>)> function)
{
	for (auto argument : arguments)
	{
		auto converted = object_cast<Number>(argument);

		function(converted);
	}
}

std::shared_ptr<Object> scripting::library::Addition::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{	
	if (arguments.size() == 0)
	{
		throw std::runtime_error("Addition expects at least one operand");
	}
	else
	{
		std::shared_ptr<Object> total = arguments[0];

		for (size_t i = 1; i < arguments.size(); ++i)
		{
			auto left = total;
			auto right = arguments[i];

			if (has_object_type<Number>(left) && has_object_type<Number>(right))
			{
				auto n1 = object_cast<Number>(left);
				auto n2 = object_cast<Number>(right);

				total = std::make_shared<Number>(n1->extract() + n2->extract());
			}
			else if (has_object_type<Vector>(left) && has_object_type<Vector>(right))
			{
				auto u = object_cast<Vector>(left);
				auto v = object_cast<Vector>(right);

				total = std::make_shared<Vector>(u->extract() + v->extract());
			}
			else if (has_object_type<Vector>(left) && has_object_type<Point>(right))
			{
				auto v = object_cast<Vector>(left);
				auto p = object_cast<Point>(right);

				total = std::make_shared<Point>(v->extract() + p->extract());
			}
			else if (has_object_type<Point>(left) && has_object_type<Vector>(right))
			{
				auto p = object_cast<Point>(left);
				auto v = object_cast<Vector>(right);

				total = std::make_shared<Point>(p->extract() + v->extract());
			}
			else
			{
				throw std::runtime_error("Incompatible types for addition");
			}
		}

		return total;
	}
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
		auto number = object_cast<Number>(arguments[0]);

		result = -number->extract();
	}
	else
	{
		result = object_cast<Number>(arguments[0])->extract();

		for (size_t i = 1; i < arguments.size(); ++i)
		{
			result -= object_cast<Number>(arguments[i])->extract();
		}
	}

	return std::make_shared<Number>(result);
}

std::shared_ptr<Object> scripting::library::Multiplication::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	double total = 1;

	for_each<Number>(arguments, [&total](std::shared_ptr<Number> number)
	{
		total *= number->extract();
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
		double last = object_cast<Number>(arguments[0])->extract();

		for (size_t i = 1; i < arguments.size(); ++i)
		{
			double current = object_cast<Number>(arguments[i])->extract();

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
		auto argument = object_cast<Boolean>(arguments[0]);

		return std::make_shared<Boolean>(!argument->extract());
	}
}

std::shared_ptr<Object> scripting::library::GetXYZ::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() != 1)
	{
		throw std::runtime_error("requires 1 argument");
	}
	else
	{
		auto argument = arguments[0];

		if (has_object_type<Point>(argument))
		{
			auto point = object_cast<Point>(argument)->extract();
			auto result = get(point);
			
			return std::make_shared<Number>(result);
		}
		else if (has_object_type<Vector>(argument))
		{
			auto vector = object_cast<Vector>(argument)->extract();
			auto result = get(vector);

			return std::make_shared<Number>(result);
		}
		else
		{
			throw std::runtime_error("Invalid type");
		}
	}
}

double scripting::library::GetX::get(const math::Point3D& p) const
{
	return p.x;
}

double scripting::library::GetX::get(const math::Vector3D& v) const
{
	return v.x;
}

double scripting::library::GetY::get(const math::Point3D& p) const
{
	return p.y;
}

double scripting::library::GetY::get(const math::Vector3D& v) const
{
	return v.y;
}

double scripting::library::GetZ::get(const math::Point3D& p) const
{
	return p.z;
}

double scripting::library::GetZ::get(const math::Vector3D& v) const
{
	return v.z;
}

std::shared_ptr<Object> scripting::library::Allocate::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() != 0)
	{
		throw std::runtime_error("Allocation requires zero arguments");
	}
	else
	{
		return std::make_shared<HeapReference>();
	}
}

std::shared_ptr<Object> scripting::library::ReadHeap::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() != 1)
	{
		throw std::runtime_error("Reading requires one argument");
	}
	else
	{
		auto readable = object_cast<Readable>(arguments[0]);

		return readable->read();
	}
}

std::shared_ptr<Object> scripting::library::WriteHeap::perform(const std::vector<std::shared_ptr<Object>>& arguments) const
{
	if (arguments.size() != 2)
	{
		throw std::runtime_error("Writing requires two argument");
	}
	else
	{
		auto writeable = object_cast<Reference>(arguments[0]);
		auto value = arguments[1];

		writeable->write(value);

		return value;
	}
}
