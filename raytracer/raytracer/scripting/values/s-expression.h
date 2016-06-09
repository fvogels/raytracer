#pragma once

#include "scripting/location.h"
#include "util/maybe.h"
#include <memory>
#include <vector>
#include <string>
#include <ostream>

namespace scripting
{
	class SExpressionVisitor;

	class SExpression
	{
	public:
		virtual void accept(SExpressionVisitor&) const = 0;
		virtual void write(std::ostream&) const = 0;
		virtual bool operator ==(const SExpression&) const = 0;

	protected:
		SExpression(const Location& location)
			: m_location(location) { }

		SExpression()
			: m_location() { }

	private:
		Maybe<Location> m_location;
	};

	class Atom : public SExpression
	{
	protected:
		Atom(const Location& location)
			: SExpression(location) { }

		Atom() { }
	};

	class List : public SExpression
	{
	public:
		List(const Location& location, const std::vector<std::shared_ptr<const SExpression>>& elements)
			: SExpression(location), m_elements(elements) { }

		List(const std::vector<std::shared_ptr<const SExpression>>& elements)
			: m_elements(elements) { }

		void accept(SExpressionVisitor&) const override;
		void write(std::ostream&) const override;
		bool operator ==(const SExpression&) const override;

		size_t size() const { return m_elements.size(); }
		std::shared_ptr<const SExpression> nth_element(size_t index) const { return m_elements[index]; }

	private:
		std::vector<std::shared_ptr<const SExpression>> m_elements;
	};

	class Symbol : public Atom
	{
	public:
		Symbol(const Location& location, const std::string& name)
			: Atom(location), m_name(name) { }

		Symbol(const std::string& name)
			: m_name(name) { }

		void accept(SExpressionVisitor&) const override;
		void write(std::ostream&) const override;
		bool operator ==(const SExpression&) const override;

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

		void accept(SExpressionVisitor&) const override;
		void write(std::ostream&) const override;
		bool operator ==(const SExpression&) const override;

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

		void accept(SExpressionVisitor&) const override;
		void write(std::ostream&) const override;
		bool operator ==(const SExpression&) const override;

	private:
		std::string string;
	};

	class Callable : public Atom
	{
	public:
		void write(std::ostream& out) const override { out << "<Callable>"; }
		bool operator ==(const SExpression&) const override { return false; }

		virtual std::shared_ptr<SExpression> call(const std::vector<SExpression>&) const = 0;
	};

	class Function : public Callable
	{
	public:
		void accept(SExpressionVisitor&) const override;
	};

	class SExpressionVisitor
	{
	public:
		virtual void visit(const String&) = 0;
		virtual void visit(const Number&) = 0;
		virtual void visit(const Symbol&) = 0;
		virtual void visit(const List&) = 0;
		virtual void visit(const Function&) = 0;
	};

	bool operator !=(const SExpression& a, const SExpression& b);
	std::ostream& operator <<(std::ostream&, const SExpression&);

	template<typename T>
	bool has_sexpression_type(const SExpression& sexpr)
	{
		return dynamic_cast<const SExpression*>(&sexpr) != nullptr;
	}

	template<typename T>
	bool has_sexpression_type(std::shared_ptr<const SExpression> sexpr)
	{
		return std::dynamic_ptr_cast<const SExpression>(sexpr) != nullptr;
	}
}