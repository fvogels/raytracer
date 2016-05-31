#pragma once

#include "scripting/location.h"
#include <memory>
#include <vector>
#include <string>

namespace scripting
{
	class SExpressionVisitor;

	class SExpression
	{
	public:
		virtual void accept(SExpressionVisitor&) const = 0;

	protected:
		SExpression(const Location& location)
			: m_location(location) { }

	private:
		Location m_location;
	};

	class Atom : public SExpression
	{
	protected:
		Atom(const Location& location)
			: SExpression(location) { }
	};

	class List : public SExpression
	{
	public:
		List(const Location& location, const std::vector<std::shared_ptr<const SExpression>>& elements)
			: SExpression(location), elements(elements) { }

		void accept(SExpressionVisitor&) const override;

	private:
		std::vector<std::shared_ptr<const SExpression>> elements;
	};

	class Symbol : public Atom
	{
	public:
		Symbol(const Location& location, const std::string& name)
			: Atom(location), name(name) { }

		void accept(SExpressionVisitor&) const override;

	private:
		std::string name;
	};

	class Number : public Atom
	{
	public:
		Number(const Location& location, double value)
			: Atom(location), value(value) { }

		void accept(SExpressionVisitor&) const override;

	private:
		double value;
	};

	class String : public Atom
	{
	public:
		String(const Location& location, const std::string& string)
			: Atom(location), string(string) { }

		void accept(SExpressionVisitor&) const override;

	private:
		std::string string;
	};

	class SExpressionVisitor
	{
	public:
		virtual void visit(const String&) = 0;
		virtual void visit(const Number&) = 0;
		virtual void visit(const Symbol&) = 0;
		virtual void visit(const List&) = 0;
	};
}