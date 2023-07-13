#include "o2s/serial.h"
#include <stdbool.h>
#include <termios.h>
#include "o2s/file_input_stream.h"

bool serial_clear(serial_port_t* port)
{
    return (tcflush(port->file.descriptor, TCIOFLUSH) == 0);
}