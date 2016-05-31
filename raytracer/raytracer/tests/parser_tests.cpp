#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/s-expression.h"
#include "scripting/tokenizer.h"
#include "scripting/parser.h"
#include "math/util.h"
#include <sstream>

using namespace scripting;

std::shared_ptr<Reader<std::shared_ptr<const Token>, Location>> create_tokenizer(std::istream& in)
{
	std::vector<std::shared_ptr<const TokenRecognizer>> recognizers{
		std::make_shared<LeftParenthesisRecognizer>(),
		std::make_shared<RightParenthesisRecognizer>(),
		std::make_shared<StringRecognizer>(),
		std::make_shared<NumberRecognizer>(),
		std::make_shared<SymbolRecognizer>()
	};

	return std::make_shared<Tokenizer>(in, recognizers);
}

std::shared_ptr<Parser> create_parser(std::istream& ss)
{
	auto tokenizer = create_tokenizer(ss);

	return std::make_shared<Parser>(tokenizer);
}

TEST_CASE("[Parser] Parsing 4", "[Parser]")
{
	std::istringstream ss("4");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == Number(4));
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing 45 12", "[Parser]")
{
	std::istringstream ss("45 12");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == Number(45));
	parser->next();
	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == Number(12));
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing ()", "[Parser]")
{
	std::istringstream ss("()");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == List(std::vector<std::shared_ptr<const SExpression>>()));
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing (5)", "[Parser]")
{
	std::istringstream ss("(5)");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == List(std::vector<std::shared_ptr<const SExpression>> { std::make_shared<const Number>(5) } ));
	parser->next();
	REQUIRE(parser->end_reached());
}

#endif
