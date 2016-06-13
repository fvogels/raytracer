#pragma once

#include <memory>
#include <vector>
#include <string>
#include <ostream>
#include <functional>

namespace scripting
{
	class Environment;
	class Heap;

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
		return dynamic_cast<const T*>(&object) != nullptr;
	}

	template<typename T>
	bool has_value_type(std::shared_ptr<const Object> object)
	{
		return std::dynamic_pointer_cast<const T>(object) != nullptr;
	}

	template<typename T, typename R>
	R with_value_type(Object& object, std::function<R(T&)> function)
	{
		auto converted = dynamic_cast<T&>(object);

		if (converted != nullptr)
		{
			return function(converted);
		}
		else
		{
			throw std::runtime_error("type error");
		}
	}

	template<typename T, typename R>
	R with_value_type(const Object& object, std::function<R(const T&)> function)
	{
		const T* converted = dynamic_cast<const T*>(&object);

		if (converted != nullptr)
		{
			return function(*converted);
		}
		else
		{
			throw std::runtime_error("type error");
		}
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

	template<typename T>
	T& value_cast(Object& object)
	{
		return with_value_type<T, T&>(object, [](T& t) -> T& {
			return t;
		});
	}

	template<typename T>
	const T& value_cast(const Object& object)
	{
		return with_value_type<T, const T&>(object, [] (const T& t) -> const T& {
			return t;
		});
	}

	template<typename T>
	std::shared_ptr<T> value_cast(std::shared_ptr<Object> object)
	{
		return with_value_type<T, std::shared_ptr<T>>(object, [](std::shared_ptr<T> t) -> std::shared_ptr<T> {
			return t;
		} );
	}
}