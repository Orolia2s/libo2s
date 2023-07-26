extern "C"
{
#include "o2s/array.h"
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("Arrays elements can be added and popped to the back", "[array]")
{
	GIVEN("An empty int array")
	{
		array_t tested = ArrayNew(int);

		THEN("It has a size of 0 and a type size of sizeof(int)")
		{
			REQUIRE( array_count(&tested) == 0 );
			REQUIRE( tested.type_size == sizeof(int) );
		}

		THEN("It has no first or last element")
		{
			REQUIRE( array_first(&tested) == NULL );
			REQUIRE( array_last(&tested) == NULL );
			REQUIRE( array_get(&tested, 0) == NULL );
		}

		THEN("It is considered empty")
		{
			REQUIRE( array_is_empty(&tested) );
		}

		WHEN("An element is appended")
		{
			int i = 42;
			array_push_back(&tested, &i);

			THEN("The size becomes 1 and the capacity is at least 1")
			{
				REQUIRE( array_count(&tested) == 1 );
				REQUIRE( tested.capacity >= 1 );
			}

			THEN("It is no longer considered empty")
			{
				REQUIRE_FALSE( array_is_empty(&tested) );
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
					REQUIRE( array_count(&tested) == 0 );
					REQUIRE( tested.capacity > 0 );
				}

				THEN("Is is considered empty again")
				{
					REQUIRE( array_is_empty(&tested) );
				}
			}
		}
	}

	GIVEN("An empty array of longs")
	{
		array_t tested = ArrayNew(long);

		THEN("It has a size of 0 and a type size of sizeof(long)")
		{
			REQUIRE( array_count(&tested) == 0 );
			REQUIRE( tested.type_size == sizeof(long) );
			REQUIRE( array_is_empty(&tested) );
		}

		WHEN("9 elements are pushed to the back")
		{
			long added[] = {1, 4, 7, 9, 2, 5, 8, 3, 6};
			size_t length = sizeof(added) / sizeof(*added);

			array_push_back_n(&tested, added, length);

			THEN("Size becomes 9, capacity at least 9")
			{
				REQUIRE( array_count(&tested) == 9 );
				REQUIRE( tested.capacity >= 9 );
				REQUIRE_FALSE( array_is_empty(&tested) );
			}

			THEN("First and last elements are correct")
			{
				REQUIRE( *(long*)array_first(&tested) == added[0] );
				REQUIRE( *(long*)array_last(&tested) == added[length - 1] );
			}

			THEN("All elements, accessed with get, are correct")
			{
				for (unsigned i = 0; i < length; i++)
				{
					REQUIRE( *(long*)array_get(&tested, i) == added[i] );
				}
			}

			THEN("It is not possible to pop 10 elements")
			{
				long destination[10];

				REQUIRE_FALSE( array_pop_back_n(&tested, destination, 10) );
			}

			WHEN("7 elements are popped")
			{
				long destination[7];

				REQUIRE( array_pop_back_n(&tested, destination, 7) );

				THEN("Only the first two elements remain")
				{
					REQUIRE( array_count(&tested) == 2 );
					REQUIRE( *(long*)array_first(&tested) == added[0] );
					REQUIRE( *(long*)array_last(&tested) == added[1] );
				}

				THEN("The popped elements are correct")
				{
					REQUIRE( memcmp(destination, added + 2, sizeof(destination)) == 0 );
				}
			}
		}
	}
}

SCENARIO("An array limits reallocations", "[array]")
{
	GIVEN("An array of doubles with 1 element")
	{
		array_t tested = ArrayNew(double);
		double  first  = 3.14;
		array_push_back(&tested, &first);

		double* initial_allocated = (double*)array_first(&tested);
		size_t  initial_capacity  = tested.capacity;

		THEN("Memory is allocated, with enough room for more than 1 element")
		{
			REQUIRE( initial_allocated != NULL );
			REQUIRE( initial_capacity > 1 );
			REQUIRE( tested.type_size == sizeof(double) );
		}

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

			WHEN("All elements are popped")
			{
				array_pop_back_n(&tested, NULL, array_count(&tested));

				THEN("The array is empty, but the capacity remains, and no reallocation has happened")
				{
					REQUIRE( array_is_empty(&tested) );
					REQUIRE( array_count(&tested) == 0 );
					REQUIRE( tested.capacity == initial_capacity );
					REQUIRE( tested.start == initial_allocated );
				}
			}
		}
	}
}

SCENARIO("We can iterate on array type", "[array]")
{
	GIVEN("An array of short with 12 element")
	{
		array_t tested  = ArrayNew(short);
		short   tab[12] = {111, 222, 333, -50, 5, 6, 7, 8, 9, 10, 516, 2123};

		array_push_back_n(&tested, tab, 12);

		THEN("The size is 12 and the capacity at least 12")
		{
			REQUIRE( array_count(&tested) == 12 );
			REQUIRE( tested.capacity >= 12 );
			REQUIRE( tested.type_size == sizeof(short) );
		}

		THEN("We can iterate over its elements conveniently")
		{
			unsigned index = 0;
			short    elt;

			array_foreach(short, &tested, &elt)
			{
				REQUIRE( elt == tab[index] );
				index++;
			}
		}

		THEN("We can iterate over its elements conveniently, with the index as well")
		{
			unsigned index = 0;
			short    elt   = -17;
			unsigned i     = 999;

			array_enumerate(short, &tested, &elt, &i)
			{
				REQUIRE( index == i );
				REQUIRE( elt == tab[index] );
				index++;
			}
		}
	}
}


SCENARIO("Array resources are correctly managed", "[array]")
{
	GIVEN("An array of 5 doubles")
	{
		array_t tested    = ArrayNew(double);
		double  content[] = {9.8, 7.6, 5.4, 3.2, 1.0};

		array_push_back_n(&tested, content, 5);

		THEN("Its capacity is greater than 5")
		{
			REQUIRE( array_count(&tested) == 5 );
			REQUIRE( tested.capacity > 5 );
		}

		WHEN("Too much memory is requested")
		{
			double* allocated = (double*)tested.start;
			REQUIRE_FALSE( array_reserve(&tested, 1024 * 1024 * 1024) );
			REQUIRE_FALSE( array_push_back_n(&tested, content, 1024 * 1024 * 1024) );

			THEN("The previous content remains untouched")
			{
				REQUIRE( allocated == tested.start );
				REQUIRE( memcmp(tested.start, content, sizeof(content)) == 0 );
			}
		}

		WHEN("The array is trimmed")
		{
			REQUIRE( array_trim(&tested) );

			THEN("The capacity becomes exactly 5")
			{
				REQUIRE( tested.capacity == 5 );
			}

			THEN("The content doesn't change")
			{
				REQUIRE( array_count(&tested) == 5 );
				REQUIRE( memcmp(tested.start, content, sizeof(content)) == 0 );
			}
		}

		WHEN("The array is cleared")
		{
			array_clear(&tested);

			THEN("It is empty, with no memory allocated")
			{
				REQUIRE( array_is_empty(&tested) );
				REQUIRE( array_count(&tested) == 0 );
				REQUIRE( tested.capacity == 0 );
				REQUIRE( tested.start == NULL );
			}
		}
	}
}
