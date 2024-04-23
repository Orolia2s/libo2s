extern "C"
{
#include "o2s/string.h"
#include "o2s/preprocessing.h"
}

#include <catch2/catch_test_macros.hpp>

#include <cstring> // strlen

TEST_CASE("Preprocessing tools behave as expected")
{
	CHECK(LIBO2S_PREPRO_ARGUMENT_COUNT(a, b, c, d, e) == 5);
	CHECK(LIBO2S_PREPRO_ARGUMENT_COUNT('1', '2', '3') == 3);
	CHECK(LIBO2S_PREPRO_ARGUMENT_COUNT("1", "2") == 2);
	CHECK(LIBO2S_PREPRO_ARGUMENT_COUNT(42314) == 1);
	CHECK(LIBO2S_PREPRO_ARGUMENT_COUNT() == 0);
}

TEST_CASE("A string can be created from a literal", "[string][hashes]")
{
	String empty  = string_from_literal("");

	CHECK( FNV1A() == string_fnv1a_32(&empty) );
	CHECK( FNV1A_0() == cstring_fnv1a_32("", 0) );

	String tested = string_from_literal("A quote");
	CHECK( FNV1A('A',' ','q','u','o','t','e') == string_fnv1a_32(&tested));
	CHECK( FNV1A('A',' ','q','u','o','t','e') == cstring_fnv1a_32("A quote", std::strlen("A quote")));

	CHECK( FNV1A('A', 'b') != FNV1A('b', 'A'));
}
