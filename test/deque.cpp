extern "C"
{
#include "o2s/deque.h"
#include "o2s/queue.h"
}

#include <catch2/catch_test_macros.hpp>

#include <climits> // ULONG_MAX

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
				REQUIRE( *(int*)deque_get(&tested, 0) == pushed );
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
				REQUIRE( *(int*)deque_get(&tested, 0) == pushed );
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
			 7, 81, 64,  6, 28, 62,  8, 99};

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

			THEN("The values are correct")
			{
				REQUIRE( *(int*)deque_first(&tested) == pushed[0] );
				REQUIRE( *(int*)deque_last(&tested) == pushed[capacity - 1] );
				for (unsigned i = 0; i < deque_count(&tested); i++)
				{
					REQUIRE( *(int*)deque_get(&tested, i) == pushed[i] );
				}
			}

			THEN("More elements can't be pushed")
			{
				int extra = 456;
				REQUIRE_FALSE( deque_push_back(&tested, &extra) );
				REQUIRE_FALSE( deque_push_front(&tested, &extra) );

				int extras[5] = {1, 2, 3, 4, 5};
				REQUIRE_FALSE( deque_push_back_n(&tested, extras, 5) );
				REQUIRE_FALSE( deque_push_front_n(&tested, extras, 5) );
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

		WHEN("45 elements are pushed to the front")
		{
			deque_push_front_n(&tested, pushed, capacity);

			THEN("It has a size of 45, is no longer empty, capacity didn't change, and is full")
			{
				REQUIRE( deque_count(&tested) == capacity );
				REQUIRE( deque_capacity(&tested) == capacity );
				REQUIRE( deque_is_full(&tested) );
				REQUIRE_FALSE( deque_is_empty(&tested) );
			}

			THEN("The values are correct")
			{
				REQUIRE( *(int*)deque_first(&tested) == pushed[capacity - 1] );
				REQUIRE( *(int*)deque_last(&tested) == pushed[0] );
				for (unsigned i = 0; i < deque_count(&tested); i++)
				{
					REQUIRE( *(int*)deque_get(&tested, i) == pushed[capacity - 1 - i] );
				}
			}

			THEN("More elements can't be pushed")
			{
				int extra = 456;
				REQUIRE_FALSE( deque_push_back(&tested, &extra) );
				REQUIRE_FALSE( deque_push_front(&tested, &extra) );

				int extras[5] = {1, 2, 3, 4, 5};
				REQUIRE_FALSE( deque_push_back_n(&tested, extras, 5) );
				REQUIRE_FALSE( deque_push_front_n(&tested, extras, 5) );
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
					for (unsigned i = 0; i < 10; i++)
					{
						REQUIRE( popped[i] == pushed[capacity - 1 - i] );
					}
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
						REQUIRE( popped[i] == pushed[i] );
					}
				}

				THEN("More than 35 elements cannot be popped")
				{
					int out[40];
					REQUIRE_FALSE( deque_pop_front_n(&tested, out, 36) );
					REQUIRE_FALSE( deque_pop_back_n(&tested, out, 36) );
				}
			}
		}
	}
}

SCENARIO("Resources are correctly managed", "[deque]")
{
	WHEN("Allocation fails")
	{
		deque_t tested = DequeAllocate(ULONG_MAX / sizeof(double) / 2, double);

		THEN("Capacity is marked as 0")
		{
			REQUIRE( tested.capacity == 0 );
			REQUIRE( tested.storage == NULL );
		}
	}

	GIVEN("An allocated deque")
	{
		deque_t tested = DequeAllocate(1024, double);

		WHEN("It is freed")
		{
			deque_free(&tested);

			THEN("The capacity is marked as 0")
			{
				REQUIRE( tested.capacity == 0 );
				REQUIRE( tested.storage == NULL );
			}
		}
	}
}

SCENARIO("The can be discontinuous", "[deque]")
{
	GIVEN("A deque with elements already pushed back and popped front")
	{
		const size_t capacity = 47;
		Deque tested = DequeAllocate(capacity, short);

		short pushed[] = {
			90, 32, 78, 54, 12, 31, 48, 76, 14, 15,
			92, 65, 35, 89, 79, 32, 38, 46, 26, 43,
			38, 32, 79, 50, 28, 84, 19, 71, 69, 39,
			93, 75, 10, 58, 20, 97, 49, 44, 59, 23,
			 7, 81, 64,  6, 28, 62,  8, 99};

		REQUIRE( deque_push_back_n(&tested, pushed, 13) );
		REQUIRE( deque_pop_front_n(&tested, NULL, 13) );

		THEN("It is in the expected state")
		{
			REQUIRE( deque_is_empty(&tested) );
			REQUIRE( deque_capacity(&tested) == capacity );
			REQUIRE( tested.type_size == sizeof(short) );
		}

		WHEN("It is filled, creating a split")
		{
			REQUIRE( deque_push_back_n(&tested, pushed, capacity) );

			THEN("All elements can be accessed with get")
			{
				REQUIRE( *(short*)deque_first(&tested) == pushed[0] );
				REQUIRE( *(short*)deque_last(&tested) == pushed[capacity - 1] );
				REQUIRE( deque_get(&tested, capacity) == NULL );

				for (size_t i = 0; i < deque_count(&tested); i++)
				{
					REQUIRE( *(short*)deque_get(&tested, i) == pushed[i] );
				}
			}

			THEN("Elements can be iterated over with a for each loop")
			{
				short element;
				short* pointer = pushed;

				deque_foreach(short, &tested, &element)
				{
					REQUIRE( element == *pointer );
					pointer++;
				}
			}

			THEN("Elements can be iterated over with the index, as a for loop")
			{
				short element;
				unsigned index = 0;
				unsigned i = 0;

				deque_enumerate(short, &tested, &element, &index)
				{
					REQUIRE( element == pushed[i] );
					REQUIRE( index == i );
					i++;
				}
			}

			THEN("All elements can be popped in one call")
			{
				short out[50];

				REQUIRE( deque_pop_front_n(&tested, out, capacity) );

				for (unsigned i = 0; i < capacity; i++)
					REQUIRE( out[i] == pushed[i] );
			}
		}
	}
}

TEST_CASE("Deque of chars", "[deque]")
{
	Deque tested = DequeAllocate(17, char);
	char popped[2];

	REQUIRE( deque_push_back(&tested, "N") );
	REQUIRE( deque_push_back_n(&tested, "goodO", strlen("goodO")) );
	REQUIRE( deque_pop_front(&tested, popped) );
	CHECK( popped[0] == 'N' );
	REQUIRE( deque_pop_back(&tested, popped + 1) );
	CHECK( popped[1] == 'O' );
	REQUIRE( deque_push_front_n(&tested, " yrev", strlen(" yrev")) );

	const char expected[] = "very good";
	for (unsigned i = 0; i < deque_count(&tested); i++)
	{
		CHECK( *(char*)deque_get(&tested, i) == expected[i] );
	}
	char c;
	unsigned index;
	deque_enumerate(char, &tested, &c, &index)
	{
		CHECK( c == expected[index] );
	}
}

TEST_CASE("Deque of size_t", "[deque]")
{
	Deque tested = DequeAllocate(17, size_t);
	const size_t pushed[20] = {5, 6, 7, 8, 9, 888, 0, 4, 3, 2, 1, 777};
	size_t popped[2];

	REQUIRE( deque_push_back(&tested, pushed + 11) );
	REQUIRE( deque_push_back_n(&tested, pushed, 6) );
	REQUIRE( deque_pop_front(&tested, popped) );
	CHECK( popped[0] == 777 );
	REQUIRE( deque_pop_back(&tested, popped + 1) );
	CHECK( popped[1] == 888 );
	REQUIRE( deque_push_front_n(&tested, pushed + 6, 5) );

	const size_t expected[] = {1, 2, 3, 4, 0, 5, 6, 7, 8, 9};
	for (unsigned i = 0; i < deque_count(&tested); i++)
	{
		CHECK( *(size_t*)deque_get(&tested, i) == expected[i] );
	}
	size_t c;
	unsigned index;
	deque_enumerate(size_t, &tested, &c, &index)
	{
		CHECK( c == expected[index] );
	}
}

TEST_CASE("Deque of as a queue", "[deque]")
{
	Queue tested = QueueAllocate(20, float);
	float values[] = {6.28, 1.61, 2.71};
	float popped;

	REQUIRE( queue_push(&tested, values) );
	REQUIRE( queue_push(&tested, values + 1) );
	REQUIRE( queue_pop(&tested, &popped) );
	REQUIRE( queue_push(&tested, values + 2) );
	CHECK( popped == values[0] );
	CHECK( *(float*)queue_first(&tested) == values[1] );
	CHECK( *(float*)queue_get(&tested, 1) == values[2] );
	CHECK( queue_capacity(&tested) >= 3 );
}

SCENARIO("We can reserve capacity", "[deque]")
{
	GIVEN("An empty deque of ints with a capacity of 45")
	{
		const size_t capacity = 45;
		Deque tested = DequeAllocate(capacity, int);

		WHEN("A capacity of 40 elements is reserved")
		{
			deque_reserve(&tested, 40);

			THEN("The current capacity is already enough, capacity didn't change")
			{
				REQUIRE( deque_capacity(&tested) == capacity );
			}
		}

		WHEN("A capacity of 50 elements is reserved")
		{
			int reserved = 50;
			deque_reserve(&tested, reserved);

			THEN("The current capacity is not enough, capacity changed")
			{
				REQUIRE( deque_capacity(&tested) == capacity + reserved );
			}
		}

		WHEN("A too big capacity is reserved")
		{
			deque_reserve(&tested, ULONG_MAX / sizeof(int) / 2);

			THEN("Capacity is marked as 0")
			{
				REQUIRE( deque_capacity(&tested) == 0 );
				REQUIRE( tested.storage == NULL );
			}
		}
	}
}
