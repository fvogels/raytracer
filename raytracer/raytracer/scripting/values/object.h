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

	class List : public Object
	{
	public:
		List(const std::vector<std::shared_ptr<Object>>&);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		size_t size() const;
		std::shared_ptr<const Object> nth_element(size_t index) const;

	private:
		std::vector<std::shared_ptr<Object>> m_elements;
	};

	class Symbol : public Object
	{
	public:
		Symbol(const std::string&);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		std::string name() const { return m_name; }

	private:
		std::string m_name;
	};

	

	class String : public Object
	{
	public:
		String(const std::string&);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		std::string value() const;

	private:
		std::string string;
	};

	class Callable : public Object
	{
	public:
		void write(std::ostream& out) const override { out << "<Callable>"; }
		bool operator ==(const Object&) const override { return false; }

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		virtual std::shared_ptr<Object> call(std::shared_ptr<scripting::Environment>, const std::vector<std::shared_ptr<Object>>&) const = 0;
	};

	class Function : public Callable
	{
	public:
		std::shared_ptr<Object> call(std::shared_ptr<scripting::Environment>, const std::vector<std::shared_ptr<Object>>&) const override;

	protected:
		virtual std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const = 0;
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