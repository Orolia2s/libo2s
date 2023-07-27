extern "C"
{
#include "o2s/string.h"
}

#include <catch2/catch_test_macros.hpp>

TEST_CASE("A string can be created from a literal", "[string]")
{
	String tested = string_from_literal("A funny quote");

	REQUIRE( string_length(&tested) == strlen("A funny quote") );
	REQUIRE( strcmp(string_to_cstring(&tested), "A funny quote") == 0 );
}

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
				REQUIRE( *string_get(&tested, 0) == '*' );
			}
		}

		WHEN("A literal is appended")
		{
			const char*  content = "A string Literal";
			const size_t length  = strlen(content);

			REQUIRE( string_append_literal(&tested, "A string Literal") );

			THEN("The content is as expected")
			{
				REQUIRE( string_length(&tested) == length );
				REQUIRE( memcmp(string_to_cstring(&tested), content, length) == 0 );
				REQUIRE( strcmp(string_to_cstring(&tested), content) == 0 );
			}
		}

		WHEN("A literal, a char and a string are appended")
		{
			String copied = string_from_literal("Monde");

			REQUIRE( string_append_literal(&tested, "Bonjour") );
			REQUIRE( string_append_char(&tested, ' ') );
			REQUIRE( string_append(&tested, &copied) );

			THEN("The content is as expected")
			{
				REQUIRE( string_length(&tested) == strlen("Bonjour Monde") );
				REQUIRE( strcmp(string_to_cstring(&tested), "Bonjour Monde") );
			}
		}
	}
}
