#pragma once

#include "scripting/tokenizing/tokens.h"
#include "scripting/reader.h"
#include "scripting/values/object.h"
#include <memory>
#include <stack>
#include <list>

namespace scripting
{
	class ParsingVisitor;

	class Parser : public Reader<std::shared_ptr<Object>, Location>
	{
	public:
		Parser(std::shared_ptr<Reader<std::shared_ptr<const Token>, Location>>);
		~Parser();

		bool end_reached() const override;
		std::shared_ptr<Object> current() const override;
		void next() override;
		Location location() const override;

	private:
		std::shared_ptr<Reader<std::shared_ptr<const Token>, Location>> m_reader;
		std::shared_ptr<Object> m_object;
		std::unique_ptr<ParsingVisitor> m_visitor;

		void extract_next_object();
	};
}