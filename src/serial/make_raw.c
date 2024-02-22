/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file make_raw.c                                                           */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/log.h"
#include "o2s/serial.h"

#include <termios.h> // tcsetattr

#include <errno.h>
#include <iso646.h>  // not
#include <string.h>  // strerror

/**
 * Modify the copy of the options, but do not apply them
 * @see serial_make_raw
 */
bool serial_set_options_raw(serial_port_t* port)
{
	if (not serial_get_options(port))
		return false;

	port->options.input.ignore_break          = false;
	port->options.input.signal_break          = false;
	port->options.input.mark_errors           = false;
	port->options.input.strip_8th_bit         = false;
	port->options.input.map_nl_to_cr          = false;
	port->options.input.ignore_cr             = false;
	port->options.input.map_cr_to_nl          = false;
	port->options.input.enable_start_stop_out = false;

	port->options.output.enable_processing = false;

	port->options.control.character_size = character_size_8;
	port->options.control.enable_parity  = false;

	port->options.local.enable_signals    = false;
	port->options.local.canonical         = false;
	port->options.local.echo              = false;
	port->options.local.echo_nl           = false;
	port->options.local.enable_processing = false;

	/* Not mentionned in documentation */
	port->options.control_characters.timeout = 0;
	port->options.control_characters.minimum = 1;

	return true;
}

/** Modify the copy of the options about speed, but do not apply them. */
bool serial_set_options_speed(serial_port_t* port, int64_t speed_bps)
{
	speed_t speed = serial_encode_baudrate(speed_bps);

	if (speed == 0)
	{
		log_error("%li is not a valid baudrate, refer to termios(3) for further details", speed_bps);
		return false;
	}
	if (not serial_get_options(port))
		return false;
	port->options.input_speed              = speed;
	port->options.output_speed             = speed;
	port->options.input._dont_modify_speed = false;
	port->options.control._speed_4lsb      = speed;
	port->options.control._speed_is_extra  = speed >> 12;
	return true;
}

/**
 * General configuration for non-canonical mode
 *
 * Sets the terminal to something like the "raw" mode of the old Version 7 terminal
 * driver: input is available character by character, echoing is disabled, and
 * all special processing of terminal input and output characters is disabled.
 */
bool serial_make_raw(serial_port_t* port, int64_t speed_bps)
{
	if (not(serial_set_options_raw(port) and serial_set_options_speed(port, speed_bps)
	        and serial_apply_options(port)))
		return false;
	return true;
}
