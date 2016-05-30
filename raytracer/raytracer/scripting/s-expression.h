#pragma once

#include "scripting/location.h"
#include <memory>
#include <vector>
#include <string>

namespace scripting
{
	class SExpression
	{
	public:
		virtual ~SExpression() { }

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

	private:
		std::vector<std::shared_ptr<const SExpression>> elements;
	};

	class Symbol : public Atom
	{
	public:
		Symbol(const Location& location, const std::string& name)
			: Atom(location), name(name) { }

	private:
		std::string name;
	};

	class Number : public Atom
	{
	public:
		Number(const Location& location, double value)
			: Atom(location), value(value) { }

	private:
		double value;
	};

	class String : public Atom
	{
	public:
		String(const Location& location, const std::string& string)
			: Atom(location), string(string) { }

	private:
		std::string string;
	};
}