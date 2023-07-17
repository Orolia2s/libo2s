#include "o2s/file_input_stream.h"
#include "o2s/serial.h"

#include <termios.h>

#include <stdbool.h>

bool serial_clear(serial_port_t* port)
{
	return (tcflush(port->file.descriptor, TCIOFLUSH) == 0);
}