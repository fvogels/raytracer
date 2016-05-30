#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/tokenizer.h"
#include "math/util.h"
#include <sstream>

using namespace scripting;

bool is_lparen(std::shared_ptr<const Token> token)
{
	return has_token_type<LeftParenthesisToken>(token);
}

bool is_rparen(std::shared_ptr<const Token> token)
{
	return has_token_type<RightParenthesisToken>(token);
}

bool is_string(std::shared_ptr<const Token> token, std::string string)
{
	if (has_token_type<StringToken>(token))
	{
		auto string_token = std::dynamic_pointer_cast<const StringToken>(token);

		return string_token->string == string;
	}
	else
	{
		return false;
	}
}

bool is_number(std::shared_ptr<const Token> token, double value)
{
	if (has_token_type<NumberToken>(token))
	{
		auto number_token = std::dynamic_pointer_cast<const NumberToken>(token);

		return number_token->value == approx(value);
	}
	else
	{
		return false;
	}
}

TEST_CASE("[Tokenizer] Empty stream", "[Tokenizer]")
{
	std::stringstream ss("");
	Tokenizer reader(ss);

	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing (", "[Tokenizer]")
{
	std::stringstream ss("(");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_lparen(reader.current()));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing )", "[Tokenizer]")
{
	std::stringstream ss(")");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_rparen(reader.current()));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing ()", "[Tokenizer]")
{
	std::stringstream ss("()");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_lparen(reader.current()));
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(is_rparen(reader.current()));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\"", "[Tokenizer]")
{
	std::stringstream ss("\"abc\"");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "abc"));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\" \"xyz\"", "[Tokenizer]")
{
	std::stringstream ss("\"abc\" \"xyz\"");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "abc"));
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "xyz"));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\"     \"xyz\"", "[Tokenizer]")
{
	std::stringstream ss("\"abc\"     \"xyz\"");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "abc"));
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "xyz"));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\"\\n\"xyz\"", "[Tokenizer]")
{
	std::stringstream ss("\"abc\"\n\"xyz\"");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "abc"));
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "xyz"));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\" ; Hello\\n\"xyz\"", "[Tokenizer]")
{
	std::stringstream ss("\"abc\" ; Hello\n\"xyz\"");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "abc"));
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "xyz"));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\" ; Hello\\n     \"xyz\"", "[Tokenizer]")
{
	std::stringstream ss("\"abc\" ; Hello\n     \"xyz\"");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "abc"));
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(is_string(reader.current(), "xyz"));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing 1", "[Tokenizer]")
{
	std::stringstream ss("1");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_number(reader.current(), 1));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing 12", "[Tokenizer]")
{
	std::stringstream ss("12");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_number(reader.current(), 12));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing 1 2", "[Tokenizer]")
{
	std::stringstream ss("1 2");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(is_number(reader.current(), 1));
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(is_number(reader.current(), 2));
	reader.next();
	REQUIRE(reader.end_reached());
}

#endif