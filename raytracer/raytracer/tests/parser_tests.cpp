#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/values.h"
#include "scripting/tokenizing/tokenizer.h"
#include "scripting/parser.h"
#include "math/util.h"
#include <sstream>

using namespace scripting;

static std::shared_ptr<Reader<std::shared_ptr<const Token>, Location>> create_tokenizer(std::istream& in)
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

static std::shared_ptr<Parser> create_parser(std::istream& ss)
{
	auto tokenizer = create_tokenizer(ss);

	return std::make_shared<Parser>(tokenizer);
}

static std::shared_ptr<Object> number(double x)
{
	return std::make_shared<Number>(x);
}

static std::shared_ptr<Object> string(const std::string& str)
{
	return std::make_shared<String>(str);
}

static std::shared_ptr<Object> symbol(const std::string& str)
{
	return std::make_shared<Symbol>(str);
}

static std::shared_ptr<Object> list(const std::vector<std::shared_ptr<Object>>& elts)
{
	return std::make_shared<List>(elts);
}

#define LIST(...) list(std::vector<std::shared_ptr<Object>> { __VA_ARGS__ } )

TEST_CASE("[Parser] Parsing 4", "[Parser]")
{
	std::istringstream ss("4");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == Number(4));
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing ~4", "[Parser]")
{
	std::istringstream ss("~4");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == Number(-4));
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
	REQUIRE(*parser->current() == *LIST());
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing (5)", "[Parser]")
{
	std::istringstream ss("(5)");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == *LIST(number(5)));
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing (+ 2 3)", "[Parser]")
{
	std::istringstream ss("(+ 2 3)");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == *LIST(symbol("+"), number(2), number(3)));
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing (+ (* 1 2) 3)", "[Parser]")
{
	std::istringstream ss("(+ (* 1 2) 3)");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == *LIST(symbol("+"), LIST(symbol("*"), number(1), number(2)), number(3)));
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing () ()", "[Parser]")
{
	std::istringstream ss("() ()");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == *LIST());
	parser->next();
	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == *LIST());
	parser->next();
	REQUIRE(parser->end_reached());
}

TEST_CASE("[Parser] Parsing ()()", "[Parser]")
{
	std::istringstream ss("()()");
	auto parser = create_parser(ss);

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == *LIST());
	parser->next();
	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == *LIST());
	parser->next();
	REQUIRE(parser->end_reached());
}

#endif
