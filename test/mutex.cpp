extern "C"
{
#include "o2s/mutex.h"

#include "o2s/file_input_stream.h"
}

#include <catch2/catch_test_macros.hpp>

#include <cerrno>

SCENARIO("We can use mutexes with a RAII style", "[mutex]")
{
	GIVEN("A mutex")
	{
		pthread_mutex_t my_mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;

		WHEN("It is locked")
		{
			O2sLockGuard _ = o2s_mutex_lock(&my_mutex);

			THEN("Locking it again fails")
			{
				REQUIRE(pthread_mutex_trylock(&my_mutex) == EBUSY);
			}
		}
		THEN("It is unlocked after the scope")
		{
			REQUIRE(pthread_mutex_trylock(&my_mutex) == 0);
			REQUIRE(pthread_mutex_unlock(&my_mutex) == 0);
		}
	}
}
