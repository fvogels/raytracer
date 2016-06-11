#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/interpreter.h"
#include "scripting/tokenizer.h"
#include "scripting/parser.h"
#include "scripting/values.h"
#include "scripting/standard-library.h"
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

static std::shared_ptr<Object> parse(const std::string& input)
{
	std::istringstream ss(input);
	auto parser = create_parser(ss);

	return parser->current();
}

static std::shared_ptr<Environment> create_environment()
{
	auto result = std::make_shared<Environment>();

	scripting::add_standard_library_bindings(result.get());

	return result;
}

static std::shared_ptr<Object> interpret(const std::string& input)
{
	auto parsed_input = parse(input);
	
	return evaluate(parsed_input, create_environment());
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

static std::shared_ptr<Object> boolean(bool b)
{
	return std::make_shared<Boolean>(b);
}

#define TEST(sexpr, expected) TEST_CASE("[interpret] Evaluating " #sexpr, "[interpreter]") { auto result = interpret(sexpr); REQUIRE(*result == *expected); }


TEST("5", number(5));
TEST("\"abc\"", string("abc"));
TEST("(+)", number(0));
TEST("(+ 7)", number(7));
TEST("(+ 5 3)", number(8));
TEST("(+ 5 3 1)", number(9));
TEST("(*)", number(1));
TEST("(* 3)", number(3));
TEST("(* 2 7)", number(14));
TEST("(* (+ 5 2) 7)", number(49));
TEST("(-)", number(0));
TEST("(- 5)", number(-5));
TEST("(- 5 3)", number(2));
TEST("(- 5 3 1)", number(1));
TEST("(let ((x 5)) x)", number(5));
TEST("(let ((x 5) (y 3)) (+ x y))", number(8));
TEST("true", boolean(true));
TEST("false", boolean(false));
TEST("(= 5 3)", boolean(false));
TEST("(= 5 5)", boolean(true));
TEST("(= (+ 3 2) 5)", boolean(true));

#endif
