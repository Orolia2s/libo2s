/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/**
 * @copyright 2023-2024, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file into_array.c
 * @author Antoine GAGNIERE
 * @brief Move elements from a deque to an array
 */
/* ************************************************************************** */

#include "o2s/array.h"
#include "o2s/deque.h"

#include <iso646.h> // not

/**
 * Move the @p count first elements at the back of @p destination
 */
bool deque_pop_front_into_array(deque_t* self, struct array* destination, size_t count)
{
	if (not array_reserve(destination, count))
		return false;
	if (not deque_pop_front_n(self, array_end(destination), count))
		return false;
	destination->count += count;
	return true;
}
