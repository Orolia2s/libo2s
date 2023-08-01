extern "C"
{
#include "o2s/to_string.h"
}

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <iostream>
#include <limits>

TEST_CASE("Strings can be created from integer types", "[to_string]")
{
	SECTION("int")
	{
		int i = GENERATE(0, 100, -42, 256, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
		String tested = int_to_string(&i);

		CHECK( std::to_string(i) == string_to_cstring(&tested) );
	}

	SECTION("short")
	{
		short i = GENERATE(0, 100, -42, 256, std::numeric_limits<short>::min(), std::numeric_limits<short>::max());
		String tested = short_to_string(&i);

		CHECK( std::to_string(i) == string_to_cstring(&tested) );
	}

	SECTION("long")
	{
		long i = GENERATE(0, 100, -42, 256, std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
		String tested = long_to_string(&i);

		CHECK( std::to_string(i) == string_to_cstring(&tested) );
	}

	SECTION("unsigned")
	{
		unsigned i = GENERATE(0, 100, 256, std::numeric_limits<unsigned>::max());
		String tested = unsigned_to_string(&i);

		CHECK( std::to_string(i) == string_to_cstring(&tested) );
	}

	SECTION("Empty array")
	{
		Array array = ArrayNew(int);
		String tested = array_to_string(&array, (string_t (*)(const void*))int_to_string);

		CHECK( std::string(string_to_cstring(&tested)) == "[]" );
	}

	SECTION("Empty deque")
	{
		Deque deque = DequeAllocate(23, short);
		String tested = deque_to_string(&deque, (string_t (*)(const void*))short_to_string);

		CHECK( std::string(string_to_cstring(&tested)) == "[]" );
	}

	SECTION("Array of long")
	{
		const long content[]  = {123, -8754, 98662, -136859, 3, 21, 0, -100001};
		const unsigned length = sizeof(content) / sizeof(*content);
		Array          array  = ArrayNew(long);

		array_push_back_n(&array, content, length);
		String tested = array_to_string(&array, (string_t (*)(const void*))long_to_string);
		CHECK(std::string(string_to_cstring(&tested)) == "[123, -8754, 98662, -136859, 3, 21, 0, -100001]");
	}

	SECTION("Deque of unsigned")
	{
		const unsigned content[] = {123, 8754, 98662, 136859, 2012345, 3, 1, 4, 1, 5, 9, 2};
		const unsigned length = sizeof(content) / sizeof(*content);
		Deque          deque  = DequeAllocate(16, unsigned);

		CHECK( deque.type_size == sizeof(unsigned) );

		/* Force data to be split */
		deque_push_back_n(&deque, content, 8);
		deque_pop_front_n(&deque, NULL, 8);
		deque_push_back_n(&deque, content, length);

		String tested = deque_to_string(&deque, (string_t(*)(const void*))unsigned_to_string);

		CHECK(std::string(string_to_cstring(&tested)) == "[123, 8754, 98662, 136859, 2012345, 3, 1, 4, 1, 5, 9, 2]");
	}
}
