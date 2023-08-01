/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/*
 * @copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED
 * @file queue.c
 * @author Antoine GAGNIERE
 * @brief Realtime FIFO buffer
 */
/* ************************************************************************** */

#include "o2s/queue.h"

void queue_free(queue_t* self)
{
	deque_free(self);
}

bool queue_push(queue_t* self, const void* element)
{
	return deque_push_back(self, element);
}

bool queue_push_n(queue_t* self, const void* elements, size_t count)
{
	return deque_push_back_n(self, elements, count);
}

bool queue_pop(queue_t* self, void* destination)
{
	return deque_pop_front(self, destination);
}

bool queue_pop_n(queue_t* self, void* destination, size_t count)
{
	return deque_pop_front_n(self, destination, count);
}

size_t queue_room(const queue_t* self)
{
	return deque_room(self);
}

size_t queue_count(const queue_t* self)
{
	return deque_count(self);
}
