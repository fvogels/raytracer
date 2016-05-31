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

std::shared_ptr<Parser> create_parser(const std::string& string)
{
	std::istringstream ss("4");
	auto tokenizer = create_tokenizer(ss);

	return std::make_shared<Parser>(tokenizer);
}

TEST_CASE("[Parser] Parsing 4", "[Parser]")
{
	auto parser = create_parser("4");

	REQUIRE(!parser->end_reached());
	REQUIRE(*parser->current() == Number(4));
}


#endif
