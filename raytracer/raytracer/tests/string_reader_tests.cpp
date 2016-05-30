#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/reader.h"
#include "scripting/string_reader.h"
#include <sstream>

using namespace scripting;

TEST_CASE("[StringReader] Empty string", "[StringReader]")
{
	StringReader reader("");

	REQUIRE(reader.end_reached());
}

TEST_CASE("[StringReader] Single character", "[StringReader]")
{
	StringReader reader("a");

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'a');
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[StringReader] Two characters", "[StringReader]")
{
	StringReader reader("ab");

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'a');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'b');
	reader.next();
	REQUIRE(reader.end_reached());
}

#endif
