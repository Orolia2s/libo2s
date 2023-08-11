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

	char out[30] = {};
	REQUIRE( queue_pop_n(&tested.buffer, out, strlen("Hello ")) );
	REQUIRE( queue_pop_n(&tested.buffer, NULL, strlen("cruel ")) );
	REQUIRE( queue_pop_n(&tested.buffer, out + strlen("Hello "), strlen("world")) );

	CHECK_FALSE( istream_accumulate(&tested, 1) );
	CHECK( strcmp(out, "Hello world") == 0 );
}

TEST_CASE("String input streams from literals", "[stream]")
{
	StringInputStream tested = string_literal_input_stream("Hello CRUEL world");

	REQUIRE( istream_accumulate(&tested, 10) );
	REQUIRE_FALSE( istream_accumulate(&tested, strlen("Hello cruel world") + 1) );

	char out[30] = {};
	REQUIRE( queue_pop_n(&tested.buffer, out, strlen("Hello ")) );
	REQUIRE( queue_pop_n(&tested.buffer, NULL, strlen("cruel ")) );
	REQUIRE( queue_pop_n(&tested.buffer, out + strlen("Hello "), strlen("world")) );

	CHECK_FALSE( istream_accumulate(&tested, 1) );
	CHECK( strcmp(out, "Hello world") == 0 );
}
