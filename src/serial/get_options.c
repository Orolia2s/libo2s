/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file get_options.c                                                        */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/log.h"
#include "o2s/serial.h"

#include <termios.h> // tcgetattr

#include <errno.h>
#include <stdbool.h>
#include <string.h> // strerror

/**
 * Ask the port for its configuration.
 */
bool serial_get_options(serial_port_t* port)
{
	if (port->got_options)
		return true;
	if (tcgetattr(port->file.descriptor, &port->options.termios) != 0)
	{
		log_error("Unable to get the attributes of the terminal: %s", strerror(errno));
		return false;
	}
	port->got_options = true;
	return true;
}
