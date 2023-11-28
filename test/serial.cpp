extern "C"
{
#include "o2s/serial.h"

#include <termios.h>
}

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <utility>

TEST_CASE("We can convert baudrate constants to and from bps rates", "[serial]")
{
	SECTION("Decoding an invalid value yields -1")
	{
		speed_t value = GENERATE(50, 300, 4096);

		CHECK( serial_decode_baudrate(value) == -1 );
	}

	SECTION("Encoding an invalid value yields 0")
	{
		long value = GENERATE(25, 100, 500, 100000);

		CHECK( serial_encode_baudrate(value) == 0 );
	}

	std::pair<long, speed_t> rate =
	    GENERATE((std::pair<long, speed_t>){0, B0},
	             (std::pair<long, speed_t>){50, B50},
	             (std::pair<long, speed_t>){75, B75},
	             (std::pair<long, speed_t>){110, B110},
	             (std::pair<long, speed_t>){134, B134},
	             (std::pair<long, speed_t>){150, B150},
	             (std::pair<long, speed_t>){200, B200},
	             (std::pair<long, speed_t>){300, B300},
	             (std::pair<long, speed_t>){600, B600},
	             (std::pair<long, speed_t>){1200, B1200},
	             (std::pair<long, speed_t>){1800, B1800},
	             (std::pair<long, speed_t>){2400, B2400},
	             (std::pair<long, speed_t>){4800, B4800},
	             (std::pair<long, speed_t>){9600, B9600},
	             (std::pair<long, speed_t>){19200, B19200},
	             (std::pair<long, speed_t>){38400, B38400},
	             (std::pair<long, speed_t>){57600, B57600},
	             (std::pair<long, speed_t>){115200, B115200},
	             (std::pair<long, speed_t>){230400, B230400},
	             (std::pair<long, speed_t>){460800, B460800},
	             (std::pair<long, speed_t>){500000, B500000},
	             (std::pair<long, speed_t>){576000, B576000},
	             (std::pair<long, speed_t>){921600, B921600},
	             (std::pair<long, speed_t>){1000000, B1000000},
	             (std::pair<long, speed_t>){1152000, B1152000},
	             (std::pair<long, speed_t>){1500000, B1500000},
	             (std::pair<long, speed_t>){2000000, B2000000},
	             (std::pair<long, speed_t>){2500000, B2500000},
	             (std::pair<long, speed_t>){3000000, B3000000},
	             (std::pair<long, speed_t>){3500000, B3500000},
	             (std::pair<long, speed_t>){4000000, B4000000});
	CHECK( serial_encode_baudrate(std::get<long>(rate)) == std::get<speed_t>(rate) );
	CHECK( serial_decode_baudrate(std::get<speed_t>(rate)) == std::get<long>(rate) );
}

TEST_CASE("We can set a serial port raw", "[serial]")
{
	uint8_t       initial = GENERATE(0, 0xFF);
	serial_port_t ours = {.got_options = true};
	serial_port_t std;

	memset(&std.options, initial, sizeof(std.options));
	memset(&ours.options, initial, sizeof(ours.options));

	cfmakeraw(&std.options.termios);
	REQUIRE( serial_set_options_raw(&ours) );

	CHECK( memcmp(&std.options, &ours.options, sizeof(std.options)) == 0 );
}
