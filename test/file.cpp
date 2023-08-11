extern "C"
{
#include "o2s/file_input_stream.h"

#include <fcntl.h> // O_RDONLY

#include <unistd.h> // close
}

#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <filesystem> // path
#include <fstream>    // ofstream
#include <functional> // lambdas
#include <string>
#include <thread>

SCENARIO("Errors when reading files are correctly handled", "[file]")
{
	GIVEN("The name of an unexisting file")
	{
		const char* file_name = "does_not_exist.txt";

		WHEN("We try to open it")
		{
			FileInputStream tested = file_open(file_name, O_RDONLY);

			THEN("We get a negative file descriptor")
			{
				REQUIRE( tested.descriptor < 0 );
				REQUIRE_FALSE( tested.opened );
			}
		}
	}

	GIVEN("An existing file, that we open and close")
	{
		const std::filesystem::path folder   = std::filesystem::temp_directory_path();
		const std::filesystem::path filename = folder / "dummy_file_for_tests.txt";

		{
			std::ofstream file(filename, std::ios::trunc);

			file << "Bonjour";
		}

		FileInputStream tested = file_open(filename.c_str(), O_RDONLY);
		CHECK( close(tested.descriptor) == 0 );

		WHEN("We try to accumulate bytes from it")
		{
			bool result = istream_accumulate(&tested, 10);

			THEN("The accumulating loop exits with an error")
			{
				REQUIRE_FALSE( result );
			}
		}

		std::filesystem::remove(filename);
	}
}

SCENARIO("A regular file can be read", "[file]")
{
	GIVEN("A file with known content")
	{
		const std::filesystem::path folder   = std::filesystem::temp_directory_path();
		const std::filesystem::path filename = folder / "dummy_file_for_tests.txt";
		const std::string           content  = "_Hello_ Bonjour _Nihao_";

		{
			std::ofstream file(filename, std::ios::trunc);

			file << content;
		}

		WHEN("We open it")
		{
			FileInputStream tested = file_open(filename.c_str(), O_RDONLY);

			THEN("It is opened successfully")
			{
				REQUIRE( tested.opened );
				REQUIRE( tested.descriptor >= 0 );
			}

			AND_WHEN("We read from it")
			{
				ssize_t count = file_single_read(&tested);

				THEN("The right amount of char was read")
				{
					REQUIRE( count > 0 );
					REQUIRE( (size_t)count == content.length() );

					AND_WHEN("The read characters are moved out of the buffer")
					{
						char again[count + 1];

						explicit_bzero(again, count + 1);
						REQUIRE( queue_pop_n(&tested.stream.buffer, again, count) );

						THEN("They are as expected")
						{
							REQUIRE( std::string(again) == content );
						}
					}

					AND_WHEN("We try to read again")
					{
						ssize_t too_much = file_single_read(&tested);

						THEN("We get 0 character")
						{
							REQUIRE( too_much == 0 );
						}
					}
				}
			}
		}
	}
}

SCENARIO("A stream can be accumulated", "[file]")
{
	GIVEN("A file with only part of the content")
	{
		const std::filesystem::path folder   = std::filesystem::temp_directory_path();
		const std::filesystem::path filename = folder / "dummy_file_for_tests.txt";

		{
			std::ofstream file(filename, std::ios::trunc);

			file << "Bonjour";
		}

		WHEN("We need to read the whole content")
		{
			FileInputStream tested = file_open(filename.c_str(), O_RDONLY);

			THEN("It waits")
			{
				char        extract[99] = {0};
				std::thread worker([&]()
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(25));
						std::ofstream file(filename, std::ios::app);
						file << " Monde";
					});

				REQUIRE( istream_accumulate(&tested, strlen("Bonjour Monde")) ); // <-- will wait here
				REQUIRE( queue_pop_n(&tested.stream.buffer, extract, queue_count(&tested.stream.buffer)) );
				REQUIRE( std::string(extract) == "Bonjour Monde" );
				worker.join();
			}
		}

		std::filesystem::remove(filename);
	}
}
