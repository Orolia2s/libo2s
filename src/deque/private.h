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
 * @file private.h
 * @author Hugo FOLCHER
 * @author Antoine GAGNIERE
 */
/* ************************************************************************** */

#include "o2s/deque.h"

void*  deque_begin(const deque_t* self);
void*  deque_end(const deque_t* self);

size_t deque_offset(const deque_t* self, size_t count);
size_t deque_distance(const deque_t* self, void* one, void* two);

void*  deque_pointer_before(const deque_t* self, void* pointer);
void*  deque_pointer_after(const deque_t* self, void* pointer);
