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

		WHEN("A character is appended")
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
			const char*  content = "A string Literal OMG";
			const size_t length  = strlen(content);

			REQUIRE( string_append_literal(&tested, content) );

			THEN("The content is as expected")
			{
				REQUIRE( string_length(&tested) == length );
				REQUIRE( memcmp(string_to_cstring(&tested), content, length) == 0 );
				REQUIRE( strcmp(string_to_cstring(&tested), content) == 0 );

				for (unsigned i = 0; i < length; i++)
				{
					REQUIRE( *string_get(&tested, i) == content[i] );
				}
			}

			THEN("We can iterate over the characters")
			{
				char c;
				unsigned i;
				unsigned index = 0;

				string_foreach(&tested, &c)
				{
					REQUIRE( c == content[index] );
					index++;
				}
				REQUIRE( index == length );

				index = 0;
				string_enumerate(&tested, &c, &i)
				{
					REQUIRE( i == index );
					REQUIRE( c == content[index] );
					index++;
				}
				REQUIRE( index == length );
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
				REQUIRE( strcmp(string_to_cstring(&tested), "Bonjour Monde") == 0 );
				REQUIRE_FALSE( string_is_empty(&tested) );
			}

			AND_WHEN("The characters are popped in different ways")
			{
				char popped[10];
				char space;

				REQUIRE( string_pop_n(&tested, popped, strlen("Monde")) );
				REQUIRE( string_pop(&tested, &space) );

				String hello = string_pop_as_string(&tested, strlen("Bonjour"));

				THEN("The popped characters are correct")
				{
					REQUIRE( strcmp(popped, "Monde") == 0 );
					REQUIRE( space == ' ' );
					REQUIRE( string_length(&hello) == strlen("Bonjour") );
					REQUIRE( strcmp(string_to_cstring(&hello), "Bonjour") == 0);
				}

				THEN("The string is considered empty, but kept its storage space")
				{
					REQUIRE( string_is_empty(&tested) );
					REQUIRE( tested.capacity >= strlen("Bonjour Monde") );
				}
			}

			AND_WHEN("Too much characters are popped as a string")
			{
				String toomuch = string_pop_as_string(&tested, 20);

				THEN("That string is empty")
				{
					REQUIRE( string_length(&toomuch) == 0 );
					REQUIRE( toomuch.capacity == 0 );
				}
			}
		}
	}
}

TEST_CASE("String to C string conversion can fail", "[string]")
{
	String tested = string_from_literal(
		"Some long string that fills exactly the capacity"
		"And for some reason the RAM cannot fit a single more char"
		);

	CHECK( string_trim(&tested) );
	tested.type_size = 1024UL * 1024 * 1024 * 97; // for the reserve(1) to fail
	REQUIRE(string_to_cstring(&tested) == NULL);
}
