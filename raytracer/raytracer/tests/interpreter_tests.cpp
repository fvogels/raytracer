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
}

#endif
