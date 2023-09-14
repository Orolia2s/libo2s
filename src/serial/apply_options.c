/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file apply_options.c
 * @author Antoine GAGNIERE
 */
/* ************************************************************************** */

#include "o2s/log.h"
#include "o2s/serial.h"

#include <termios.h> // tcsetattr

#include <errno.h>
#include <iso646.h> // not
#include <stdbool.h>
#include <string.h> // strerror

/** Apply the options immediatly */
bool serial_apply_options(serial_port_t* port)
{
	if (not port->got_options)
		return false;
	if (tcsetattr(port->file.descriptor, TCSANOW, &port->options.termios) != 0)
	{
		log_error("Unable to apply the attributes of the terminal: %s", strerror(errno));
		return false;
	}
	port->got_options = false;
	return true;
}
