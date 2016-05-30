#include "scripting/tokenizer.h"
#include "scripting/combined_reader.h"
#include "scripting/stream_line_reader.h"
#include "scripting/string_reader.h"
#include <assert.h>
#include <cctype>

using namespace scripting;

scripting::Tokenizer::Tokenizer(std::istream& in)
	: m_reader(in)
{
	if (!m_reader.end_reached())
	{
		tokenize();
	}
}

void scripting::Tokenizer::tokenize()
{
	assert(!m_reader.end_reached());

	skip_whitespace_and_comments();

	if (!m_reader.end_reached())
	{
		char c = m_reader.current();

		assert(!isspace(c));
		assert(!m_reader.end_reached());

		if (c == '(')
		{
			tokenize_lparen();
		}
		else if (c == ')')
		{
			tokenize_rparen();
		}
		else if (c == '"')
		{
			tokenize_string();
		}
		else
		{
			throw std::runtime_error("Unrecognized character " + c);
		}
	}
	else
	{
		m_current_token = nullptr;
	}
}

void scripting::Tokenizer::tokenize_lparen()
{
	assert(!m_reader.end_reached());
	assert(m_reader.current() == '(');

	m_current_token = std::make_shared<LeftParenthesisToken>(m_reader.location());
	m_reader.next();
}

void scripting::Tokenizer::tokenize_rparen()
{
	assert(!m_reader.end_reached());
	assert(m_reader.current() == ')');

	m_current_token = std::make_shared<RightParenthesisToken>(m_reader.location());
	m_reader.next();
}

void scripting::Tokenizer::tokenize_string()
{
	assert(!m_reader.end_reached());
	assert(m_reader.current() == '"');

	std::string buffer;
	Location start_location = m_reader.location();
	
	m_reader.next();
	while (!m_reader.end_reached())
	{
		if (m_reader.current() == '"')
		{
			goto tokenize_string_success;
		}
		else
		{
			buffer += m_reader.current();
			m_reader.next();
		}
	}

	assert(m_reader.end_reached());
	throw std::runtime_error("Unexpected eof while reading string");

tokenize_string_success:
	assert(!m_reader.end_reached());
	assert(m_reader.current() == '"');

	m_reader.next();
	m_current_token = std::make_shared<StringToken>(start_location, buffer);
}

void scripting::Tokenizer::skip_whitespace()
{
	while (!m_reader.end_reached() && isspace(m_reader.current()))
	{
		m_reader.next();
	}
}

void scripting::Tokenizer::skip_comments()
{
	assert(!m_reader.end_reached());
	assert(m_reader.current() == ';');

	while (!m_reader.end_reached())
	{
		if (m_reader.current() == '\n')
		{
			m_reader.next();
			return;
		}
		else
		{
			m_reader.next();
		}
	}
}

void scripting::Tokenizer::skip_whitespace_and_comments()
{
	while (true)
	{
		skip_whitespace();

		if (!m_reader.end_reached() && m_reader.current() == ';')
		{
			skip_comments();
		}
		else
		{
			return;
		}
	}
}

std::shared_ptr<Token> scripting::Tokenizer::current() const
{
	assert(!end_reached());
	assert(m_current_token != nullptr);

	return m_current_token;
}

bool scripting::Tokenizer::end_reached() const
{
	return m_current_token == nullptr;
}

void scripting::Tokenizer::next()
{
	assert(!end_reached());

	tokenize();
}

Location scripting::Tokenizer::location() const
{
	assert(!end_reached());

	return m_reader.location();
}