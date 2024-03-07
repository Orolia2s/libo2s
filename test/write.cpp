extern "C"
{
#include "o2s/write.h" // write_all

#include "o2s/deque.h"
#include "o2s/file_input_stream.h"
#include "o2s/log.h"
#include "o2s/string.h"

#include <fcntl.h> // O_RDONLY

#include <stdio.h>  // tmpfile, fileno
#include <unistd.h> // open, write, read
}

#include <catch2/catch_test_macros.hpp>

SCENARIO("We can write to a file descriptor with guarantees", "[write]")
{
	GIVEN("A huge number of bytes")
	{
		size_t  length   = 8'000'000;
		int     random   = open("/dev/random", O_RDONLY);
		String  to_write = string_new();
		ssize_t was_read;

		REQUIRE(string_reserve(&to_write, length));
		was_read = read(random, to_write.start, to_write.capacity);
		REQUIRE(was_read > 0);
		to_write.count = was_read;

		THEN("We can write it with a single call")
		{
			FILE*   out = tmpfile();

			CHECK(write_all(fileno(out), (char*)to_write.start, to_write.count));

			AND_THEN("The right bytes were written")
			{
				String was_written = string_new();

				REQUIRE(string_reserve(&was_written, to_write.count));
				rewind(out);
				was_read = read(fileno(out), (char*)was_written.start, was_written.capacity);
				REQUIRE(was_read > 0);
				was_written.count = was_read;
				CHECK(string_is_equal(&to_write, &was_written));
			}
		}
	}
}
