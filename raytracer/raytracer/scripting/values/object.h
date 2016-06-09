#pragma once

#include "scripting/location.h"
#include "util/maybe.h"
#include <memory>
#include <vector>
#include <string>
#include <ostream>

namespace scripting
{
	class ObjectVisitor;

	class Object
	{
	public:
		virtual void accept(ObjectVisitor&) const = 0;
		virtual void write(std::ostream&) const = 0;
		virtual bool operator ==(const Object&) const = 0;

	protected:
		Object(const Location&);
		Object();

	private:
		Maybe<Location> m_location;
	};

	class Atom : public Object
	{
	protected:
		Atom(const Location& location)
			: Object(location) { }

		Atom() { }
	};

	class List : public Object
	{
	public:
		List(const Location& location, const std::vector<std::shared_ptr<const Object>>& elements)
			: Object(location), m_elements(elements) { }

		List(const std::vector<std::shared_ptr<const Object>>& elements)
			: m_elements(elements) { }

		void accept(ObjectVisitor&) const override;
		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		size_t size() const { return m_elements.size(); }
		std::shared_ptr<const Object> nth_element(size_t index) const { return m_elements[index]; }

	private:
		std::vector<std::shared_ptr<const Object>> m_elements;
	};

	class Symbol : public Atom
	{
	public:
		Symbol(const Location& location, const std::string& name)
			: Atom(location), m_name(name) { }

		Symbol(const std::string& name)
			: m_name(name) { }

		void accept(ObjectVisitor&) const override;
		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::string name() const { return m_name; }

	private:
		std::string m_name;
	};

	class Number : public Atom
	{
	public:
		Number(const Location& location, double value)
			: Atom(location), value(value) { }

		Number(double value)
			: value(value) { }

		void accept(ObjectVisitor&) const override;
		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

	private:
		double value;
	};

	class String : public Atom
	{
	public:
		String(const Location& location, const std::string& string)
			: Atom(location), string(string) { }

		String(const std::string& string)
			: string(string) { }

		void accept(ObjectVisitor&) const override;
		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

	private:
		std::string string;
	};

	class Callable : public Atom
	{
	public:
		void write(std::ostream& out) const override { out << "<Callable>"; }
		bool operator ==(const Object&) const override { return false; }

		virtual std::shared_ptr<Object> call(const std::vector<Object>&) const = 0;
	};

	class Function : public Callable
	{
	public:
		void accept(ObjectVisitor&) const override;
	};

	class ObjectVisitor
	{
	public:
		virtual void visit(const String&) = 0;
		virtual void visit(const Number&) = 0;
		virtual void visit(const Symbol&) = 0;
		virtual void visit(const List&) = 0;
		virtual void visit(const Function&) = 0;
	};

	bool operator !=(const Object& a, const Object& b);
	std::ostream& operator <<(std::ostream&, const Object&);

	template<typename T>
	bool has_sexpression_type(const Object& sexpr)
	{
		return dynamic_cast<const Object*>(&sexpr) != nullptr;
	}

	template<typename T>
	bool has_sexpression_type(std::shared_ptr<const Object> sexpr)
	{
		return std::dynamic_ptr_cast<const Object>(sexpr) != nullptr;
	}
}