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
 * @file queue.h
 * @author Antoine GAGNIERE
 * @brief Realtime FIFO buffer
 */
/* ************************************************************************** */

#include "o2s/deque.h"

typedef deque_t queue_t;

#define Queue         Deque
#define QueueAllocate DequeAllocate

void   queue_free(queue_t* self);

/** @name Modifiers */
///@{
bool   queue_push(queue_t* self, const void* element);
bool   queue_push_n(queue_t* self, const void* elements, size_t count);

bool   queue_pop(queue_t* self, void* destination);
bool   queue_pop_n(queue_t* self, void* destination, size_t count);
///@}

/** @name Element access */
///@{
void*  queue_first(const queue_t* self);
void*  queue_get(const queue_t* self, size_t index);
///@}

/** @name Capacity */
///@{
size_t queue_room(const queue_t* self);
size_t queue_count(const queue_t* self);
///@}
