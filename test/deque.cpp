extern "C"
{
#include "o2s/deque.h"
#include <stdio.h>
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("We can populate a deque", "[deque]")
{
	uint8_t   tab[60] = {111, 222, 33, 50, 5, 6, 7, 8, 9, 10, 16, 123, 111, 222, 33, 50, 5, 6, 7, 8, 9, 10, 16, 223, 111, 222, 33, 50, 5, 6, 7, 8, 9, 10, 16, 223, 111, 222, 33, 50, 5, 6, 7, 8, 9, 10, 56, 223, 111, 222, 33, 50, 5, 6, 7, 8, 9, 10, 16, 223};

	GIVEN("An empty deque with a capacity of 45")
	{
		int capacity = 45;
		void* p = malloc(sizeof(uint8_t) * capacity);
		REQUIRE(p != NULL);
		deque_t tested  = DequeNew(p, uint8_t, capacity);
		REQUIRE(tested.capacity == capacity);
		REQUIRE(tested.type_size == sizeof(uint8_t));
		REQUIRE(deque_count(&tested) == 0);

		WHEN("1 element is pushed at the front")
		{
			deque_push_front(&tested, (void*) tab);


			REQUIRE(*((uint8_t*) tested.first) == tab[0]);
			REQUIRE(deque_count(&tested) == 1);

			WHEN("1 elements are poped front")
			{
				uint8_t popped_element;
				REQUIRE(deque_pop_front(&tested, &popped_element));
				REQUIRE(deque_count(&tested) == 0);
				REQUIRE(popped_element == tab[0]);
			}
		}
	}

	GIVEN("An empty deque with a capacity of 45")
	{
		int capacity = 45;
		void* p = malloc(sizeof(uint8_t) * capacity);
		REQUIRE(p != NULL);
		deque_t tested  = DequeNew(p ,uint8_t, capacity);
		REQUIRE(tested.capacity == capacity);
		REQUIRE(tested.type_size == sizeof(uint8_t));
		REQUIRE(deque_count(&tested) == 0);

		WHEN("20 elements are pushed front")
		{
			deque_push_front_n(&tested, (void*) tab, 20);
			REQUIRE(deque_count(&tested) == 20);

			WHEN("20 elements are poped front")
			{
				uint8_t popped_element[20];
				REQUIRE(deque_pop_front_n(&tested, popped_element, 20));
				REQUIRE(deque_count(&tested) == 0);
				for (size_t i = 0; i < 20; i++)
				{
					REQUIRE(popped_element[i] == tab[19 - i]);
				}
			}
		}
	}

	GIVEN("An empty deque with a capacity of 45")
	{
		int capacity = 45;
		void* p = malloc(sizeof(uint8_t) * capacity);
		REQUIRE(p != NULL);
		deque_t tested  = DequeNew(p ,uint8_t, capacity);
		REQUIRE(tested.capacity == capacity);
		REQUIRE(tested.type_size == sizeof(uint8_t));
		REQUIRE(deque_count(&tested) == 0);

		WHEN("1 elements are pushed back")
		{
			REQUIRE(deque_count(&tested) == 0);
			deque_push_back(&tested, (void*) tab);
			REQUIRE(deque_count(&tested) == 1);

			WHEN("1 elements are popped back")
			{
				uint8_t popped_element[1];
				REQUIRE(deque_pop_back(&tested, popped_element));
				REQUIRE(deque_count(&tested) == 0);
				for (size_t i = 0; i < 1; i++)
				{
					REQUIRE(popped_element[i] == tab[0 - i]);
				}
			}
		}
	}

	GIVEN("An empty deque with a capacity of 45")
	{
		int capacity = 45;
		void* p = malloc(sizeof(uint8_t) * capacity);
		REQUIRE(p != NULL);
		deque_t tested  = DequeNew(p ,uint8_t, capacity);
		REQUIRE(tested.capacity == capacity);
		REQUIRE(tested.type_size == sizeof(uint8_t));
		REQUIRE(deque_count(&tested) == 0);

		WHEN("20 elements are pushed back")
		{
			REQUIRE(deque_count(&tested) == 0);
			deque_push_back_n(&tested, (void*) tab, 20);
			REQUIRE(deque_count(&tested) == 20);

			WHEN("20 elements are popped back")
			{
				uint8_t popped_element[20];
				REQUIRE(deque_pop_back_n(&tested, popped_element, 20));
				REQUIRE(deque_count(&tested) == 0);
				for (size_t i = 0; i < 20; i++)
				{
					REQUIRE(popped_element[i] == tab[19 - i]);
				}
			}
		}
	}

	GIVEN("An empty deque with a capacity of 45")
	{
		int capacity = 45;
		void* p = malloc(sizeof(uint8_t) * capacity);
		REQUIRE(p != NULL);
		deque_t tested  = DequeNew(p ,uint8_t, capacity);
		REQUIRE(tested.capacity == capacity);
		REQUIRE(tested.type_size == sizeof(uint8_t));
		REQUIRE(deque_count(&tested) == 0);

		WHEN("10 elements are pushed back and 10 other are pushed front then popped")
		{
			REQUIRE(deque_count(&tested) == 0);
			deque_push_back_n(&tested, (void*) tab, 10);
			REQUIRE(deque_count(&tested) == 10);

			deque_push_front_n(&tested, (void*) tab, 10);
			REQUIRE(deque_count(&tested) == 20);


			uint8_t popped_element[10];
			REQUIRE(deque_pop_back_n(&tested, popped_element, 10));
			REQUIRE(deque_count(&tested) == 10);
			for (size_t i = 0; i < 10; i++)
			{
				REQUIRE(popped_element[i] == tab[9 - i]);
			}

			REQUIRE(deque_pop_front_n(&tested, popped_element, 10));
			REQUIRE(deque_count(&tested) == 0);
			for (size_t i = 0; i < 10; i++)
			{
				REQUIRE(popped_element[i] == tab[9 - i]);
			}
		}
	}

	GIVEN("An empty deque with a capacity of 45")
	{
		int capacity = 45;
		void* p = malloc(sizeof(uint8_t) * capacity);
		REQUIRE(p != NULL);
		deque_t tested  = DequeNew(p ,uint8_t, capacity);
		REQUIRE(tested.capacity == capacity);
		REQUIRE(tested.type_size == sizeof(uint8_t));
		REQUIRE(deque_count(&tested) == 0);

		WHEN("10 elements are pushed back and 10 other are pushed front")
		{
			REQUIRE(deque_count(&tested) == 0);
			deque_push_back_n(&tested, (void*) tab, 10);
			REQUIRE(deque_count(&tested) == 10);

			deque_push_front_n(&tested, (void*) tab, 10);
			REQUIRE(deque_count(&tested) == 20);

			WHEN("deque is cleared")
			{
				deque_clear(&tested);
				REQUIRE(tested.first_index == tested.end_index);
				REQUIRE(deque_count(&tested) == 0);
				WHEN("10 elements are pushed back and 10 other are pushed front")
				{
					REQUIRE(deque_count(&tested) == 0);
					deque_push_back_n(&tested, (void*) tab, 10);
					REQUIRE(deque_count(&tested) == 10);

					deque_push_front_n(&tested, (void*) tab, 10);
					REQUIRE(deque_count(&tested) == 20);
					WHEN("10 elements are popped back then 10 elements are popped front")
					{
						uint8_t popped_element[10];
						REQUIRE(deque_pop_back_n(&tested, popped_element, 10));
						REQUIRE(deque_count(&tested) == 10);
						for (size_t i = 0; i < 10; i++)
						{
							REQUIRE(popped_element[i] == tab[9 - i]);
						}

						REQUIRE(deque_pop_front_n(&tested, popped_element, 10));
						REQUIRE(deque_count(&tested) == 0);
						for (size_t i = 0; i < 10; i++)
						{
							REQUIRE(popped_element[i] == tab[9 - i]);
						}
					}
				}
			}
		}
	}
	GIVEN("An empty deque with a capacity of 10")
	{
		int capacity = 10;
		void* p = malloc(sizeof(uint8_t) * capacity);
		REQUIRE(p != NULL);
		deque_t tested  = DequeNew(p ,uint8_t, capacity);

		REQUIRE(tested.capacity == capacity);
		REQUIRE(tested.type_size == sizeof(uint8_t));
		REQUIRE(deque_count(&tested) == 0);

		WHEN("10 elements are pushed back")
		{
			REQUIRE(deque_count(&tested) == 0);
			REQUIRE(deque_push_back_n(&tested, (void*) tab, 10));
			REQUIRE(deque_count(&tested) == 10);
			REQUIRE(deque_room(&tested) == 0);
		}
		WHEN("1 more elements is pushed back")
		{
			REQUIRE(deque_push_back_n(&tested, (void*) tab, 10));
			REQUIRE(deque_count(&tested) == 10);
			REQUIRE(deque_push_back(&tested, (void*) tab) == false);
			REQUIRE(deque_count(&tested) == 10);
		}
	}
}
