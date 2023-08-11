extern "C"
{
#include "o2s/string_input_stream.h"
}

#include <catch2/catch_test_macros.hpp>

TEST_CASE("String input streams", "[stream]")
{
	String            value  = string_from_literal("Hello cruel world");
	StringInputStream tested = string_input_stream(&value);

	REQUIRE( istream_accumulate(&tested, 10) );
	REQUIRE_FALSE( istream_accumulate(&tested, strlen("Hello cruel world") + 1) );
}
