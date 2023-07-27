extern "C"
{
#include "o2s/string.h"
}

#include <catch2/catch_test_macros.hpp>


SCENARIO("Strings can be manipulated intuitively", "[string]")
{
	GIVEN("An empty string")
	{
		string_t tested = string_new();

		THEN("It is in the expected state")
		{
			REQUIRE( tested.type_size == sizeof(char) );
			REQUIRE( string_length(&tested) == 0 );
			REQUIRE( string_is_empty(&tested) );
		}

		WHEN("A char is appended")
		{
			REQUIRE( string_append_char(&tested, '*') );

			THEN("The length becomes 1, no longer empty")
			{
				REQUIRE( string_length(&tested) == 1 );
				REQUIRE_FALSE( string_is_empty(&tested) );
			}

			THEN("The content is this char")
			{
				REQUIRE( string_get(&tested, 0) == '*' );
				REQUIRE( *string_at(&tested, 0) == '*' );
			}
		}
	}
}
