#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/interpreter.h"
#include "scripting/tokenizer.h"
#include "scripting/parser.h"
#include "scripting/values/native-functions.h"
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

static std::shared_ptr<const Object> parse(const std::string& input)
{
	std::istringstream ss(input);
	auto parser = create_parser(ss);

	return parser->current();
}

static std::shared_ptr<Environment> create_environment()
{
	auto result = std::make_shared<Environment>();

	result->bind(Symbol("+"), std::make_shared<scripting::library::Addition>());
	result->bind(Symbol("*"), std::make_shared<scripting::library::Multiplication>());

	return result;
}

static std::shared_ptr<const Object> interpret(const std::string& input)
{
	auto parsed_input = parse(input);
	
	return evaluate(parsed_input, create_environment());
}

TEST_CASE("[evaluate] Evaluating 5", "[interpreter]")
{
	auto result = interpret("5");

	REQUIRE(has_value_type<Number>(result));

	with_value_type<Number, void>(result, [](std::shared_ptr<const Number> number) {
		REQUIRE(number->value() == Approx(5));
	});
}

TEST_CASE("[evaluate] Evaluating \"abc\"", "[interpreter]")
{
	auto result = interpret("\"abc\"");

	REQUIRE(has_value_type<String>(result));

	with_value_type<String, void>(result, [](std::shared_ptr<const String> string) {
		REQUIRE(string->value() == "abc");
	});
}

TEST_CASE("[evaluate] Evaluating (+ 5 3)", "[interpreter]")
{
	auto result = interpret("(+ 5 3)");

	REQUIRE(has_value_type<Number>(result));

	with_value_type<Number, void>(result, [](std::shared_ptr<const Number> number) {
		REQUIRE(number->value() == Approx(8));
	});
}

TEST_CASE("[evaluate] Evaluating (+ 5 3 1)", "[interpreter]")
{
	auto result = interpret("(+ 5 3 1)");

	REQUIRE(has_value_type<Number>(result));

	with_value_type<Number, void>(result, [](std::shared_ptr<const Number> number) {
		REQUIRE(number->value() == Approx(9));
	});
}

TEST_CASE("[evaluate] Evaluating (+)", "[interpreter]")
{
	auto result = interpret("(+)");

	REQUIRE(has_value_type<Number>(result));

	with_value_type<Number, void>(result, [](std::shared_ptr<const Number> number) {
		REQUIRE(number->value() == Approx(0));
	});
}

TEST_CASE("[evaluate] Evaluating (+ 7)", "[interpreter]")
{
	auto result = interpret("(+ 7)");

	REQUIRE(has_value_type<Number>(result));

	with_value_type<Number, void>(result, [](std::shared_ptr<const Number> number) {
		REQUIRE(number->value() == Approx(7));
	});
}

TEST_CASE("[evaluate] Evaluating (*)", "[interpreter]")
{
	auto result = interpret("(*)");

	REQUIRE(has_value_type<Number>(result));

	with_value_type<Number, void>(result, [](std::shared_ptr<const Number> number) {
		REQUIRE(number->value() == Approx(1));
	});
}

TEST_CASE("[evaluate] Evaluating (* 3)", "[interpreter]")
{
	auto result = interpret("(* 3)");

	REQUIRE(has_value_type<Number>(result));

	with_value_type<Number, void>(result, [](std::shared_ptr<const Number> number) {
		REQUIRE(number->value() == Approx(3));
	});
}

TEST_CASE("[evaluate] Evaluating (* 2 7)", "[interpreter]")
{
	auto result = interpret("(* 2 7)");

	REQUIRE(has_value_type<Number>(result));

	with_value_type<Number, void>(result, [](std::shared_ptr<const Number> number) {
		REQUIRE(number->value() == Approx(14));
	});
}

#endif
