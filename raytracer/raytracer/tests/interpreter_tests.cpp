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

TEST_CASE("[interpret] Evaluating 5", "[interpreter]")
{
	auto result = interpret("5");

	REQUIRE(*result == *number(5));
}

TEST_CASE("[interpret] Evaluating \"abc\"", "[interpreter]")
{
	auto result = interpret("\"abc\"");

	REQUIRE(*result == *string("abc"));
}

TEST_CASE("[interpret] Evaluating (+ 5 3)", "[interpreter]")
{
	auto result = interpret("(+ 5 3)");

	REQUIRE(*result == *number(8));
}

TEST_CASE("[interpret] Evaluating (+ 5 3 1)", "[interpreter]")
{
	auto result = interpret("(+ 5 3 1)");

	REQUIRE(*result == *number(9));
}

TEST_CASE("[interpret] Evaluating (+)", "[interpreter]")
{
	auto result = interpret("(+)");

	REQUIRE(*result == *number(0));
}

TEST_CASE("[interpret] Evaluating (+ 7)", "[interpreter]")
{
	auto result = interpret("(+ 7)");

	REQUIRE(*result == *number(7));
}

TEST_CASE("[interpret] Evaluating (*)", "[interpreter]")
{
	auto result = interpret("(*)");

	REQUIRE(*result == *number(1));
}

TEST_CASE("[interpret] Evaluating (* 3)", "[interpreter]")
{
	auto result = interpret("(* 3)");

	REQUIRE(*result == *number(3));
}

TEST_CASE("[interpret] Evaluating (* 2 7)", "[interpreter]")
{
	auto result = interpret("(* 2 7)");

	REQUIRE(*result == *number(14));
}

TEST_CASE("[interpret] Evaluating (* (+ 5 2) 7)", "[interpreter]")
{
	auto result = interpret("(* (+ 5 2) 7)");

	REQUIRE(*result == *number(49));
}

TEST_CASE("[interpret] Evaluating (-)", "[interpreter]")
{
	auto result = interpret("(-)");

	REQUIRE(*result == *number(0));
}

TEST_CASE("[interpret] Evaluating (- 5)", "[interpreter]")
{
	auto result = interpret("(- 5)");

	REQUIRE(*result == *number(-5));
}

TEST_CASE("[interpret] Evaluating (- 5 3)", "[interpreter]")
{
	auto result = interpret("(- 5 3)");

	REQUIRE(*result == *number(2));
}

TEST_CASE("[interpret] Evaluating (- 5 3 1)", "[interpreter]")
{
	auto result = interpret("(- 5 3 1)");

	REQUIRE(*result == *number(1));
}

TEST_CASE("[interpret] Evaluating (let ((x 5)) x)", "[interpreter]")
{
	auto result = interpret("(let ((x 5)) x)");

	REQUIRE(*result == *number(5));
}

TEST_CASE("[interpret] Evaluating (let ((x 5) (y 3)) (+ x y))", "[interpreter]")
{
	auto result = interpret("(let ((x 5) (y 3)) (+ x y))");

	REQUIRE(*result == *number(8));
}


#endif
