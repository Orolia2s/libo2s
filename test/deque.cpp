extern "C"
{
#include "o2s/deque.h"
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("We can populate on deque type", "[deque]")
{
	GIVEN("An deque of short with 12 element")
	{
		deque_t tested  = Deque(short, 100);
		short   tab[12] = {111, 222, 333, -50, 5, 6, 7, 8, 9, 10, 516, 2123};

		deque_push_back_n(&tested, tab, 12);

		THEN("The size is 12 and the capacity at least 12")
		{
			REQUIRE( tested.capacity >= 12 );
			REQUIRE( tested.type_size == sizeof(short) );
		}
	}
}
