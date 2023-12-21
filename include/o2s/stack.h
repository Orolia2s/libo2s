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
 * @file stack.h
 * @author Antoine GAGNIERE
 * @brief Realtime LIFO buffer
 */
/* ************************************************************************** */

#include "o2s/deque.h"

typedef deque_t stack_t;

#define stack_push   deque_push_back
#define stack_push_n deque_push_back_n

#define stack_pop    deque_pop_back
#define stack_pop_n  deque_pop_back_n
