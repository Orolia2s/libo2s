extern "C"
{
#include "o2s/array.h"
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("Arrays elements can be added to the back", "[array]")
{
	GIVEN("An empty int array")
	{
		array_t tested = Array(int);

		THEN("It has a size of 0 and a type size of sizeof(int)")
		{
			REQUIRE( tested.count == 0 );
			REQUIRE( tested.type_size == sizeof(int) );
		}

		THEN("It has no first or last element")
		{
			REQUIRE( array_first(&tested) == NULL );
			REQUIRE( array_last(&tested) == NULL );
			REQUIRE( array_get(&tested, 0) == NULL );
		}

		WHEN("An element is appended")
		{
			int i = 42;
			array_push_back(&tested, &i);

			THEN("The size becomes 1 and the capacity is at least 1")
			{
				REQUIRE( tested.count == 1 );
				REQUIRE( tested.capacity >= 1 );
			}

			THEN("The array contains the right value, acessed as first, last, or by index")
			{
				REQUIRE( *(int*)array_first(&tested) == i );
				REQUIRE( *(int*)array_last(&tested) == i );
				REQUIRE( *(int*)array_get(&tested, 0) == i );
			}

			WHEN("The element is popped")
			{
				int o;
				array_pop_back(&tested, &o);

				THEN("The popped element is the right value")
				{
					REQUIRE( o == i );
				}

				THEN("The size is 0 but the capacity remains")
				{
					REQUIRE( tested.count == 0 );
					REQUIRE( tested.capacity > 0 );
				}
			}
		}
	}
}
