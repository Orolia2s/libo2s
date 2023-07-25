extern "C"
{
#include "o2s/deque.h"
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("We can populate a deque", "[deque]")
{
	GIVEN("An empty deque of ints with a capacity of 45")
	{
		const size_t capacity = 45;
		Deque tested = DequeAllocate(capacity, int);

		THEN("It has a size of 0, a capacity of 45")
		{
			REQUIRE( deque_count(&tested) == 0 );
			REQUIRE( deque_capacity(&tested) == capacity );
			REQUIRE( deque_is_empty(&tested) );
			REQUIRE( tested.type_size == sizeof(int) );
			REQUIRE_FALSE( deque_is_full(&tested) );
		}

		THEN("It has no first nor last element")
		{
			REQUIRE( deque_first(&tested) == NULL );
			REQUIRE( deque_last(&tested) == NULL );
			REQUIRE( deque_get(&tested, 0) == NULL );
		}

		THEN("It is not possible to pop, from the front or back")
		{
			int popped;
			REQUIRE_FALSE( deque_pop_front(&tested, &popped) );
			REQUIRE_FALSE( deque_pop_back(&tested, &popped) );
		}

		WHEN("1 element is pushed to the front")
		{
			int pushed = 42;
			deque_push_front(&tested, &pushed);

			THEN("It has a size of 1, is no longer empty, capacity didn't change")
			{
				REQUIRE( deque_count(&tested) == 1 );
				REQUIRE( deque_capacity(&tested) == capacity );
				REQUIRE_FALSE( deque_is_empty(&tested) );
				REQUIRE_FALSE( deque_is_full(&tested) );
			}

			THEN("The value is correct, accessed from the front or back")
			{
				REQUIRE( *(int*)deque_first(&tested) == pushed );
				REQUIRE( *(int*)deque_last(&tested) == pushed );
			}

			WHEN("1 element is popped from the front")
			{
				int popped;
				CHECK( deque_pop_front(&tested, &popped) );

				THEN("The size becomes 0")
				{
					REQUIRE( deque_count(&tested) == 0 );
					REQUIRE( deque_capacity(&tested) == capacity );
					REQUIRE( deque_is_empty(&tested) );
					REQUIRE_FALSE( deque_is_full(&tested) );
				}

				THEN("The popped value is correct")
				{
					REQUIRE( popped == pushed );
				}
			}

			WHEN("1 element is popped from the back")
			{
				int popped;
				CHECK( deque_pop_back(&tested, &popped) );

				THEN("The size becomes 0")
				{
					REQUIRE( deque_count(&tested) == 0 );
					REQUIRE( deque_capacity(&tested) == capacity );
					REQUIRE( deque_is_empty(&tested) );
					REQUIRE_FALSE( deque_is_full(&tested) );
				}

				THEN("The popped value is correct")
				{
					REQUIRE( popped == pushed );
				}
			}
		}

		WHEN("1 element is pushed to the back")
		{
			int pushed = 42;
			deque_push_back(&tested, &pushed);

			THEN("It has a size of 1, is no longer empty, capacity didn't change")
			{
				REQUIRE( deque_count(&tested) == 1 );
				REQUIRE( deque_capacity(&tested) == capacity );
				REQUIRE_FALSE( deque_is_empty(&tested) );
				REQUIRE_FALSE( deque_is_full(&tested) );
			}

			THEN("The value is correct, accessed from the front or back")
			{
				REQUIRE( *(int*)deque_first(&tested) == pushed );
				REQUIRE( *(int*)deque_last(&tested) == pushed );
			}

			WHEN("1 element is popped from the front")
			{
				int popped;
				CHECK( deque_pop_front(&tested, &popped) );

				THEN("The size becomes 0")
				{
					REQUIRE( deque_count(&tested) == 0 );
					REQUIRE( deque_is_empty(&tested) );
				}

				THEN("The popped value is correct")
				{
					REQUIRE( popped == pushed );
				}
			}

			WHEN("1 element is popped from the back")
			{
				int popped;
				CHECK( deque_pop_back(&tested, &popped) );

				THEN("The size becomes 0")
				{
					REQUIRE( deque_count(&tested) == 0 );
					REQUIRE( deque_is_empty(&tested) );
				}

				THEN("The popped value is correct")
				{
					REQUIRE( popped == pushed );
				}
			}
		}

		int pushed[] = {
			90, 32, 78, 54, 12, 31, 48, 76, 14, 15,
			92, 65, 35, 89, 79, 32, 38, 46, 26, 43,
			38, 32, 79, 50, 28, 84, 19, 71, 69, 39,
			93, 75, 10, 58, 20, 97, 49, 44, 59, 23,
			07, 81, 64, 06, 28, 62, 08, 99};

		WHEN("45 elements are pushed to the back")
		{
			deque_push_back_n(&tested, pushed, capacity);

			THEN("It has a size of 45, is no longer empty, capacity didn't change, and is full")
			{
				REQUIRE( deque_count(&tested) == capacity );
				REQUIRE( deque_capacity(&tested) == capacity );
				REQUIRE( deque_is_full(&tested) );
				REQUIRE_FALSE( deque_is_empty(&tested) );
			}

			THEN("The value is correct, accessed from the front or back")
			{
				REQUIRE( *(int*)deque_first(&tested) == pushed[0] );
				REQUIRE( *(int*)deque_last(&tested) == pushed[capacity - 1] );
			}

			WHEN("10 element is popped from the front")
			{
				int popped[10] = {};
				CHECK( deque_pop_front_n(&tested, popped, 10) );

				THEN("The size becomes 35")
				{
					REQUIRE( deque_count(&tested) == capacity - 10 );
					REQUIRE_FALSE( deque_is_full(&tested) );
				}

				THEN("The popped values are correct")
				{
					REQUIRE( memcmp(popped, pushed, sizeof(popped)) == 0 );
				}
			}

			WHEN("10 element are popped from the back")
			{
				int popped[10] = {};
				CHECK( deque_pop_back_n(&tested, popped, 10) );

				THEN("The size becomes 35")
				{
					REQUIRE( deque_count(&tested) == capacity - 10 );
					REQUIRE_FALSE( deque_is_full(&tested) );
				}

				THEN("The popped values are correct")
				{
					for (int i = 0; i < 10; i++)
					{
						REQUIRE( popped[i] == pushed[44 - i] );
					}
				}
			}
		}
	}
}
