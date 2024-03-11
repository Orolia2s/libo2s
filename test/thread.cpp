extern "C"
{
#include "o2s/thread.h"

#include <pthread.h>
}

#include <string>

#include <catch2/catch_test_macros.hpp>

SCENARIO("A thread has a settable name", "[thread]")
{
	o2s_thread_set_name("Toto");

	CHECK( std::string(o2s_thread_name) == "Toto");

	char name[16];
	REQUIRE(pthread_getname_np(pthread_self(), name, 16) == 0);
	CHECK( std::string(name) == "Toto" );
}
