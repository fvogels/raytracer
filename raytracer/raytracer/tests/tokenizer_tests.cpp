#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/tokenizer.h"
#include <sstream>

using namespace scripting;

TEST_CASE("[Tokenizer] Empty stream", "[Tokenizer]")
{
	std::stringstream ss("");
	Tokenizer reader(ss);

	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"(\"", "[Tokenizer]")
{
	std::stringstream ss("(");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(has_token_type<LeftParenthesisToken>(reader.current()));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \")\"", "[Tokenizer]")
{
	std::stringstream ss(")");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(has_token_type<RightParenthesisToken>(reader.current()));
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"()\"", "[Tokenizer]")
{
	std::stringstream ss("()");
	Tokenizer reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(has_token_type<LeftParenthesisToken>(reader.current()));
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(has_token_type<RightParenthesisToken>(reader.current()));
	reader.next();
	REQUIRE(reader.end_reached());
}

#endif