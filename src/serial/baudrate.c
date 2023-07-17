/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file baudrate.c                                                           */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/serial.h"

#include <termios.h>

#include <stdint.h>

/**
 * Convert the baudrate from termios to bits per second
 *
 * @return
 *  - A line speed in bits per second
 *  - `-1` if the value isn't part of the possible values
 */
int64_t serial_decode_baudrate(speed_t flag)
{
	switch (flag)
	{
	case 0000000: return 0;
	case 0000001: return 50;
	case 0000002: return 75;
	case 0000003: return 110;
	case 0000004: return 134;
	case 0000005: return 150;
	case 0000006: return 200;
	case 0000007: return 300;
	case 0000010: return 600;
	case 0000011: return 1200;
	case 0000012: return 1800;
	case 0000013: return 2400;
	case 0000014: return 4800;
	case 0000015: return 9600;
	case 0000016: return 19200;
	case 0000017: return 38400;
	case 0010001: return 57600;
	case 0010002: return 115200;
	case 0010003: return 230400;
	case 0010004: return 460800;
	case 0010005: return 500000;
	case 0010006: return 576000;
	case 0010007: return 921600;
	case 0010010: return 1000000;
	case 0010011: return 1152000;
	case 0010012: return 1500000;
	case 0010013: return 2000000;
	case 0010014: return 2500000;
	case 0010015: return 3000000;
	case 0010016: return 3500000;
	case 0010017: return 4000000;
	}
	return -1;
}

// already defined in #include <termios.h>:
// B9600, B115200 ect

/**
 * Convert the baudrate to a system specific enum.
 *
 * @return
 *  - A system specific value, as define in `termios.h`
 *  - 0 if the value wasn't an accepted value.
 *
 */
speed_t serial_encode_baudrate(int64_t speed_in_bps)
{
	switch (speed_in_bps)
	{
	case 0: return 0000000;
	case 50: return 0000001;
	case 75: return 0000002;
	case 110: return 0000003;
	case 134: return 0000004;
	case 150: return 0000005;
	case 200: return 0000006;
	case 300: return 0000007;
	case 600: return 0000010;
	case 1200: return 0000011;
	case 1800: return 0000012;
	case 2400: return 0000013;
	case 4800: return 0000014;
	case 9600: return 0000015;
	case 19200: return 0000016;
	case 38400: return 0000017;
	case 57600: return 0010001;
	case 115200: return 0010002;
	case 230400: return 0010003;
	case 460800: return 0010004;
	case 500000: return 0010005;
	case 576000: return 0010006;
	case 921600: return 0010007;
	case 1000000: return 0010010;
	case 1152000: return 0010011;
	case 1500000: return 0010012;
	case 2000000: return 0010013;
	case 2500000: return 0010014;
	case 3000000: return 0010015;
	case 3500000: return 0010016;
	case 4000000: return 0010017;
	}
	return 0;
}
