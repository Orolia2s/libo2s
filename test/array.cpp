extern "C"
{
#include "o2s/array.h"
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("Arrays elements can be added and popped to the back", "[array]")
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

SCENARIO("An array limits reallocations", "[array]")
{
	GIVEN("An array of doubles with 1 element")
	{
		array_t tested = Array(double);
		double  first  = 3.14;
		array_push_back(&tested, &first);

		double* initial_allocated = (double*)array_first(&tested);
		size_t  initial_capacity  = tested.capacity;

		REQUIRE( initial_allocated != NULL );
		REQUIRE( initial_capacity > 0 );

		WHEN("More elements are appended, to fill the capacity")
		{
			size_t to_insert = initial_capacity - 1;
			while (to_insert --> 0)
			{
				double more = -123.4;
				array_push_back(&tested, &more);
			}

			THEN("The storage has not been re-allocated")
			{
				REQUIRE( tested.start == initial_allocated );
				REQUIRE( tested.capacity == initial_capacity );
			}
		}
	}
}

SCENARIO("We can iterate on array type", "[array]")
{
	GIVEN("An array of int with 12 element")
	{
		array_t tested = Array(int);
		int tab[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 516, 2123};

		array_push_back_n(&tested, tab, 12);

		WHEN("Iteration on array")
		{
			THEN("The size becomes 12 and the capacity is at least 12");
			{
				REQUIRE( tested.count == 12 );
				REQUIRE( tested.capacity >= 12 );
			}

			THEN("Test the iterator on 12 elements");
			{
				int index = 0;
				int elt;
				for_array(int, &tested, elt)
				{
					REQUIRE( elt == tab[index] );
					index ++;
				}
			}
		}
	}
}