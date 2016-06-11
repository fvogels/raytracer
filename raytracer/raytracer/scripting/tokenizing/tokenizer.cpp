#include "scripting/tokenizing/tokenizer.h"
#include "scripting/combined_reader.h"
#include "scripting/stream_line_reader.h"
#include "scripting/string_reader.h"
#include <assert.h>
#include <cctype>

using namespace scripting;

scripting::Tokenizer::Tokenizer(std::istream& in, std::vector<std::shared_ptr<const TokenRecognizer>>& recognizers)
	: m_reader(in), m_recognizers(recognizers)
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

		for (auto recognizer : m_recognizers)
		{
			if (recognizer->is_valid_start(c))
			{
				m_current_token = recognizer->tokenize(m_reader);
				return;
			}
		}
		
		throw std::runtime_error("Unrecognized character " + c);
	}
	else
	{
		m_current_token = nullptr;
	}
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

std::shared_ptr<const Token> scripting::Tokenizer::current() const
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

bool scripting::LeftParenthesisRecognizer::is_valid_start(char c) const
{
	return c == '(';
}

std::shared_ptr<Token> scripting::LeftParenthesisRecognizer::tokenize(Reader<char, Location>& reader) const
{
	assert(!reader.end_reached());
	assert(is_valid_start(reader.current()));

	Location location = reader.location();
	reader.next();

	return std::make_shared<LeftParenthesisToken>(location);
}

bool scripting::RightParenthesisRecognizer::is_valid_start(char c) const
{
	return c == ')';
}

std::shared_ptr<Token> scripting::RightParenthesisRecognizer::tokenize(Reader<char, Location>& reader) const
{
	assert(!reader.end_reached());
	assert(is_valid_start(reader.current()));

	Location location = reader.location();
	reader.next();

	return std::make_shared<RightParenthesisToken>(location);
}

bool scripting::StringRecognizer::is_valid_start(char c) const
{
	return c == '"';
}

std::shared_ptr<Token> scripting::StringRecognizer::tokenize(Reader<char, Location>& reader) const
{
	assert(!reader.end_reached());
	assert(is_valid_start(reader.current()));

	std::string buffer;
	Location start_location = reader.location();

	reader.next();
	while (!reader.end_reached())
	{
		if (reader.current() == '"')
		{
			goto tokenize_string_success;
		}
		else
		{
			buffer += reader.current();
			reader.next();
		}
	}

	assert(reader.end_reached());
	throw std::runtime_error("Unexpected eof while reading string");

tokenize_string_success:
	assert(!reader.end_reached());
	assert(reader.current() == '"');

	reader.next();
	return std::make_shared<StringToken>(start_location, buffer);
}

bool scripting::NumberRecognizer::is_valid_start(char c) const
{
	return c == '~' || c == '.' || std::isdigit(c);
}

std::shared_ptr<Token> scripting::NumberRecognizer::tokenize(Reader<char, Location>& reader) const
{
	assert(!reader.end_reached());
	assert(is_valid_start(reader.current()));

	Location start_location = reader.location();
	std::string buffer;
	bool encountered_dot = false;
	auto accumulate = [&buffer](char c) { buffer += c; };

	if (reader.current() == '~')
	{
		accumulate('-');
	}
	else
	{
		accumulate(reader.current());
	}

	reader.next();

	while (!reader.end_reached())
	{
		char c = reader.current();

		if (c == '.')
		{
			if (encountered_dot)
			{
				throw std::runtime_error("Encountered second dot in number literal");
			}
			else
			{
				encountered_dot = true;
				accumulate('.');
			}
		}
		else if (std::isdigit(c))
		{
			accumulate(c);
		}
		else
		{
			break;
		}

		reader.next();
	}

	double value = std::stod(buffer);
	return std::make_shared<NumberToken>(start_location, value);
}

bool scripting::SymbolRecognizer::is_valid_start(char c) const
{
	return is_symbol_char(c);
}

bool scripting::SymbolRecognizer::is_symbol_char(char c) const
{
	return isalnum(c) || std::string("+-*/!?@#$%^&|[]{}.,<>=").find(c) != std::string::npos;
}

std::shared_ptr<Token> scripting::SymbolRecognizer::tokenize(Reader<char, Location>& reader) const
{
	assert(!reader.end_reached());
	assert(is_valid_start(reader.current()));

	Location start_location = reader.location();
	std::string buffer;

	while (!reader.end_reached() && is_symbol_char(reader.current()))
	{
		buffer += reader.current();
		reader.next();
	}

	return std::make_shared<SymbolToken>(start_location, buffer);
}