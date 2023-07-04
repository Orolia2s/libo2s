/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file print.c                                                              */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/serial.h"

#include <stdio.h> //printf

#define WIDTH 30

static void serial_print_input_modes(const struct serial_input_modes* modes)
{
	printf("  input_modes:\n");
	printf("    %-*s: %s\n", WIDTH, "ignore_break", modes->ignore_break ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "signal_break", modes->signal_break ? "true" : "false");
	printf("    %-*s: %s\n",
	       WIDTH,
	       "discard_invalid_chars",
	       modes->discard_invalid_chars ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "mark_errors", modes->mark_errors ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "parity_check", modes->parity_check ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "strip_8th_bit", modes->strip_8th_bit ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "map_nl_to_cr", modes->map_nl_to_cr ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "ignore_cr", modes->ignore_cr ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "map_cr_to_nl", modes->map_cr_to_nl ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "map_upper_to_lower", modes->map_upper_to_lower ? "true" : "false");
	printf("    %-*s: %s\n",
	       WIDTH,
	       "enable_start_stop_out",
	       modes->enable_start_stop_out ? "true" : "false");
	printf("    %-*s: %s\n",
	       WIDTH,
	       "any_can_restart_output",
	       modes->any_can_restart_output ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "enable_start_stop_in", modes->enable_start_stop_in ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "ring_bell_when_full", modes->ring_bell_when_full ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "is_utf8", modes->is_utf8 ? "true" : "false");
	;
}

static void serial_print_output_modes(const struct serial_output_modes* modes)
{
	printf("  output_modes:\n");
	printf("    %-*s: %s\n", WIDTH, "enable_processing", modes->enable_processing ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "map_lower_to_upper", modes->map_lower_to_upper ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "map_nl_to_crnl", modes->map_nl_to_crnl ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "map_cr_to_nl", modes->map_cr_to_nl ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "no_cr", modes->no_cr ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "nl_returns", modes->nl_returns ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "use_fill", modes->use_fill ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "fill_is_del", modes->fill_is_del ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "vertical_tab_delay", modes->vertical_tab_delay ? "true" : "false");
	;
}

static void serial_print_control_modes(const struct serial_control_modes* modes)
{
	printf("  control_modes:\n");
	printf("    %-*s: %i\n", WIDTH, "character_size", 5 + modes->character_size);
	printf("    %-*s: %s\n", WIDTH, "two_stop_bits", modes->two_stop_bits ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "read", modes->read ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "enable_parity", modes->enable_parity ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "odd_parity", modes->odd_parity ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "hang_up", modes->hang_up ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "is_local", modes->is_local ? "true" : "false");
	;
}

static void serial_print_local_modes(const struct serial_local_modes* modes)
{
	printf("  local_modes:\n");
	printf("    %-*s: %s\n", WIDTH, "enable_signals", modes->enable_signals ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "canonical", modes->canonical ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "echo", modes->echo ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "echo_erasure", modes->echo_erasure ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "echo_kill", modes->echo_kill ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "echo_nl", modes->echo_nl ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "disable_flush", modes->disable_flush ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "tostop", modes->tostop ? "true" : "false");
	printf("    %-*s: %s\n", WIDTH, "enable_processing", modes->enable_processing ? "true" : "false");
	;
}

#define PRINT_UCHAR(CHARS, NAME) \
	printf("    %-*s: %#.2hhx\n", WIDTH, PP_STR(NAME), CHARS->NAME);

static void serial_print_control_characters(union serial_control_characters* chars)
{
	printf("  control_characters:\n");
	printf("    %-*s: %#.2hhx\n", WIDTH, "interrupt", chars->interrupt);
	printf("    %-*s: %#.2hhx\n", WIDTH, "quit", chars->quit);
	printf("    %-*s: %#.2hhx\n", WIDTH, "erase", chars->erase);
	printf("    %-*s: %#.2hhx\n", WIDTH, "kill", chars->kill);
	printf("    %-*s: %#.2hhx\n", WIDTH, "end_of_file", chars->end_of_file);
	printf("    %-*s: %#.2hhx\n", WIDTH, "timeout", chars->timeout);
	printf("    %-*s: %#.2hhx\n", WIDTH, "minimum", chars->minimum);
	;
}

/**
 * Output a YAML to stderr listing the status of the terminal options.
 */
bool serial_print_config(serial_port_t* port)
{
	serial_ensure_options(port);
	printf("serial_port_options:\n");
	serial_print_input_modes(&port->options.input);
	serial_print_output_modes(&port->options.output);
	serial_print_control_modes(&port->options.control);
	serial_print_local_modes(&port->options.local);
	serial_print_control_characters(&port->options.control_characters);
	printf("  baudrate:\n");
	printf("    %-*s: %hhu\n", WIDTH, "line_discipline", port->options.line_discipline);
	printf("    %-*s: %li\n",
	       WIDTH,
	       "input",
	       serial_decode_baudrate(port->options.input_speed));
	printf("    %-*s: %li\n",
	       WIDTH,
	       "output",
	       serial_decode_baudrate(port->options.output_speed));
	printf("---\n");
	return true;
}
