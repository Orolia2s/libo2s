/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file cleanup.c
 * @author Antoine GAGNIERE
 * @brief Useful for RAII
 */
/* ************************************************************************** */

#include "o2s/cleanup.h"

#include <stdlib.h> // free

/**
 * Given the address of a pointer, this pointer is passed to free if its value is not NULL
 */
void cleanup_allocated_memory(void** address)
{
	if (*address)
		free(*address);
}
