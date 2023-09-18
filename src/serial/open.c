/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file open.c                                                               */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/file_input_stream.h"
#include "o2s/serial.h"

#include <fcntl.h>

/**
 * Open the port in read-only, and allocate the buffer.
 */
serial_port_t serial_open_readonly(const char* port_name)
{
	serial_port_t port = {.file = file_open(port_name, O_RDONLY | O_NOCTTY)};
	return port;
}

/**
 * Open the port in read and write, and allocate the buffer.
 */
serial_port_t serial_open_readwrite(const char* port_name)
{
	serial_port_t port = {.file = file_open(port_name, O_RDWR | O_NOCTTY)};
	return port;
}
