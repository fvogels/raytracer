#include "scripting/parser.h"
#include <assert.h>


using namespace scripting;

class scripting::ParsingVisitor : public TokenVisitor
{
public:
	ParsingVisitor();

	void visit(const LeftParenthesisToken& token) override;
	void visit(const RightParenthesisToken&) override;
	void visit(const SymbolToken& symbol_token) override;
	void visit(const StringToken& string_token) override;
	void visit(const NumberToken& number_token) override;

	bool has_next() const;
	std::shared_ptr<const Object> current() const;
	void next();

private:
	std::stack<std::list<std::shared_ptr<const Object>>> m_stack;
	std::stack<Location> m_locations;
};

scripting::ParsingVisitor::ParsingVisitor()
{
	m_stack.push(std::list<std::shared_ptr<const Object>>());
}

void scripting::ParsingVisitor::visit(const LeftParenthesisToken& token)
{
	m_stack.push(std::list<std::shared_ptr<const Object>>());
	m_locations.push(token.location);
}

void scripting::ParsingVisitor::visit(const RightParenthesisToken&)
{
	auto elements = std::vector<std::shared_ptr<const Object>>(m_stack.top().begin(), m_stack.top().end());
	auto list = std::make_shared<List>(m_locations.top(), elements);
	m_stack.pop();
	m_locations.pop();
	m_stack.top().push_back(list);
}

void scripting::ParsingVisitor::visit(const SymbolToken& symbol_token)
{
	auto symbol = std::make_shared<Symbol>(symbol_token.location, symbol_token.name);
	m_stack.top().push_back(symbol);
}

void scripting::ParsingVisitor::visit(const StringToken& string_token)
{
	auto string = std::make_shared<String>(string_token.location, string_token.string);
	m_stack.top().push_back(string);
}

void scripting::ParsingVisitor::visit(const NumberToken& number_token)
{
	auto number = std::make_shared<Number>(number_token.location, number_token.value);
	m_stack.top().push_back(number);
}

bool scripting::ParsingVisitor::has_next() const
{
	return m_stack.top().size() == 1 && m_stack.size() == 1;
}

std::shared_ptr<const Object> scripting::ParsingVisitor::current() const
{
	return m_stack.top().front();
}

void scripting::ParsingVisitor::next()
{
	m_stack.top().pop_front();
}

scripting::Parser::Parser(std::shared_ptr<Reader<std::shared_ptr<const Token>, Location>> reader)
	: m_reader(reader), m_visitor(std::make_unique<ParsingVisitor>())
{
	extract_next_sexpression();
}

scripting::Parser::~Parser()
{
	// NOP
}

bool scripting::Parser::end_reached() const
{
	return m_sexpr == nullptr;
}

std::shared_ptr<const Object> scripting::Parser::current() const
{
	assert(!end_reached());

	return m_sexpr;
}

void scripting::Parser::next()
{
	assert(!end_reached());

	if (m_reader->end_reached())
	{
		m_sexpr = nullptr;
	}
	else
	{
		extract_next_sexpression();
	}
}

Location scripting::Parser::location() const
{
	assert(!end_reached());

	return m_reader->location();
}

void scripting::Parser::extract_next_sexpression()
{
	assert(!m_reader->end_reached());
	
	while (!m_visitor->has_next())
	{
		if (m_reader->end_reached())
		{
			throw std::runtime_error("Unfinished list");
		}
		else
		{
			auto current_token = m_reader->current();
			current_token->accept(*m_visitor);
			m_reader->next();
		}
	}

	m_sexpr = m_visitor->current();
	m_visitor->next();
}
