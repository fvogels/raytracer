#pragma once

#include "scripting/location.h"
#include <memory>
#include <vector>
#include <string>
#include <ostream>
#include <functional>

namespace scripting
{
	class Environment;

	class Object
	{
	public:
		virtual void write(std::ostream&) const = 0;
		virtual bool operator ==(const Object&) const = 0;

		virtual std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) = 0;

	protected:
		Object();
	};

	

	

	bool operator !=(const Object& a, const Object& b);
	std::ostream& operator <<(std::ostream&, const Object&);

	template<typename T>
	bool has_value_type(const Object& object)
	{
		return dynamic_cast<const Object*>(&object) != nullptr;
	}

	template<typename T>
	bool has_value_type(std::shared_ptr<const Object> object)
	{
		return std::dynamic_pointer_cast<const Object>(object) != nullptr;
	}

	template<typename T, typename R>
	R with_value_type(std::shared_ptr<Object> object, std::function<R(std::shared_ptr<T>)> function)
	{
		auto converted = std::dynamic_pointer_cast<T>(object);

		if (converted != nullptr)
		{
			return function(converted);
		}
		else
		{
			throw std::runtime_error("type error");
		}
	}
}