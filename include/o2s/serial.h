#pragma once

/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file serial.h
 * @author Antoine GAGNIERE
 */
/* ************************************************************************** */

#include "o2s/file_input_stream.h"
#include "o2s/serial_options.h"

#include <sys/types.h> // ssize_t

#include <stdbool.h>
#include <stdint.h> // uint*_t

/** Might or might not be a struct. */
typedef struct serial_port serial_port_t;

/** Serial port handler, includes a buffer */
struct serial_port
{
	ifstream_t       file;           /**< Input file buffered stream */
	serial_options_t options;        /**< Terminal options */
	uint8_t          got_options :1; /**< Is @ref options filled ? */
};

/** @name Contructor and destructor */
///@{
serial_port_t serial_open_readonly(const char* port_name);
serial_port_t serial_open_readwrite(const char* port_name);
void          serial_close(serial_port_t* port);
///@}

/** @name Modifiers */
///@{
bool          serial_get_options(serial_port_t* port);
bool          serial_apply_options(serial_port_t* port);
bool          serial_set_options_raw(serial_port_t* port);
bool          serial_make_raw(serial_port_t* port);
///@}

/** @name Utilities */
///@{
int64_t       serial_decode_baudrate(speed_t flag);
speed_t       serial_encode_baudrate(int64_t speed_in_bps);
///@}

bool          serial_print_config(serial_port_t* port);
bool          serial_clear(serial_port_t* port);

/** @see file_accumulate */
#define serial_accumulate(/* serial_port_t* */ port, /* size_t */ n) \
	file_accumulate((ifstream_t*)port, n)

/**
 * Use the RAII with serial ports.
 *
 * In a situation where one wants to declare a serial port variable
 * on the stack in the local scope, this "typedef" can be used for
 * the port to be closed automatically when the variable goes out
 * of scope.
 *
 * It means this "typedef" can only be used like this :
 * @code{.c}
 * {
 *     Serial port = serial_open(...);
 *     ...
 * } // <- The port will be closed at that point
 * @endcode
 */
#define Serial __attribute__((cleanup(serial_close))) serial_port_t
