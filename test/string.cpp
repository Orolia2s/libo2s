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
				char popped[10] = {0};
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

SCENARIO("A string created from another with a transformation")
{
	GIVEN("A string with mixed case and non alphabetic characters")
	{
		String original = string_from_literal("HelLo | BonJour + MoNde # CiAo");

		WHEN("Lowercase and uppercase versions are created")
		{
			String lower = string_tolower(&original);
			String upper = string_toupper(&original);

			THEN("The transformations worked")
			{
				REQUIRE( strcmp( string_to_cstring(&lower), "hello | bonjour + monde # ciao" ) == 0 );
				REQUIRE( strcmp( string_to_cstring(&upper), "HELLO | BONJOUR + MONDE # CIAO" ) == 0 );
			}
		}
	}
}

SCENARIO("A string can be transformed in-place")
{
	GIVEN("A string with mixed case and non alphabetic characters")
	{
		String original = string_from_literal("HelLo | BonJour + MoNde # CiAo");

		WHEN("It is tranformed to lower case")
		{
			string_tolower_inplace(&original);

			THEN("The transformation worked")
			{
				REQUIRE( strcmp( string_to_cstring(&original), "hello | bonjour + monde # ciao" ) == 0 );
			}
		}

		WHEN("It is tranformed to upper case")
		{
			string_toupper_inplace(&original);

			THEN("The transformation worked")
			{
				REQUIRE( strcmp( string_to_cstring(&original), "HELLO | BONJOUR + MONDE # CIAO" ) == 0 );
			}
		}
	}
}

TEST_CASE("Empty String", "[string]")
{
	{
		String tested = string_new();
	}
	{
		String tested = string_from_literal("");
	}
}

TEST_CASE("String comparison", "[string]")
{
	String one = string_from_literal("Some Text");
	String two = string_from_literal("Some Other Text");

	CHECK( string_is_equal(&one, &one) );
	CHECK_FALSE( string_is_equal(&one, &two) );

	REQUIRE( string_pop_n(&one, NULL, 4) );
	REQUIRE( string_append_cstring(&one, "Other Text", strlen("Other Text")) );

	CHECK( string_is_equal(&one, &two) );

	REQUIRE( string_pop_n(&one, NULL, string_length(&one)) );
	string_clear(&two);

	CHECK( string_is_equal(&one, &two) );
}

TEST_CASE("String contains", "[string]")
{
	string_t tested = string_from_literal("The crazy fox and what not");

	CHECK( string_contains(&tested, 'x') );
	CHECK( string_contains(&tested, 'y') );
	CHECK( string_contains(&tested, 'z') );
	CHECK_FALSE( string_contains(&tested, 'b') );
	CHECK_FALSE( string_contains(&tested, 'F') );
	CHECK_FALSE( string_contains(&tested, '\0') );

	REQUIRE( string_pop_n(&tested, NULL, string_length(&tested)) );
	CHECK_FALSE( string_contains(&tested, 'T') );
	string_clear(&tested);
	CHECK_FALSE( string_contains(&tested, '\0') );
}

TEST_CASE("Character is in C string", "[string]")
{
	const char* sentence = "The crazy fox and what not";

	CHECK( is_char_in_cstring('x', sentence) );
	CHECK( is_char_in_cstring('y', sentence) );
	CHECK( is_char_in_cstring('z', sentence) );
	CHECK_FALSE( is_char_in_cstring('b', sentence) );
	CHECK_FALSE( is_char_in_cstring('F', sentence) );

	/* Note that the terminating null is considered part of the C string, see man strchr */
	CHECK( is_char_in_cstring('\0', sentence) );
}
