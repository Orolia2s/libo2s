extern "C"
{
#include "o2s/version.h"

#include <string.h> // strlen, strcmp
}

#include <catch2/catch_test_macros.hpp>

TEST_CASE("We can retrieve the O2S library version as a string")
{
	const char* c_string = libo2s_version_cstring();
	String      version  = libo2s_version_string();

	REQUIRE( string_length(&version) >= 5 );
	REQUIRE( strlen(c_string) == string_length(&version) );
	REQUIRE( strcmp(c_string, string_to_cstring(&version)) == 0 );
}
