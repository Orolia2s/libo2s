extern "C"
{
#include "o2s/timer.h"

#include "o2s/file_input_stream.h"
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("A timer interrupts an infinite read", "[timer]")
{
	REQUIRE(o2s_timer_setup_process());

	GIVEN("A timer")
	{
		O2sTimer timer = o2s_timer_create();

		WHEN("It is armed")
		{
			ArmedTimer _ = o2s_timer_start(timer, 20);

			THEN("It interrupts a read")
			{
				FileInputStream hello = file_from_descriptor(0);
				CHECK_FALSE(file_accumulate_infinite(&hello, 14));
			}
		}
	}
}
