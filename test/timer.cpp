extern "C"
{
#include "o2s/timer.h"

#include "o2s/file_input_stream.h"
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("A timer interrupts an infinite read", "[timer]")
{
	REQUIRE(o2s_timer_setup_process(file_default_signal_handler));

	GIVEN("A timer")
	{
		O2sTimer timer = o2s_timer_create();
		REQUIRE(timer.created);

		WHEN("It is armed")
		{
			ArmedTimer armed_timer = o2s_timer_start(timer, 20);
			REQUIRE(armed_timer.armed);

			THEN("It interrupts a read")
			{
				FileInputStream hello = file_from_descriptor(0);
				CHECK_FALSE(file_accumulate_infinite(&hello, 14));
			}
		}
		file_resume_reading();
	}
}
