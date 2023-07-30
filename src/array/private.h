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
 */
/* ************************************************************************** */

#include "o2s/array.h"

/** Number of elements allocated at minimum */
#define ARRAY_INITIAL_SIZE  16
/** Factor used to multiply the capacity with */
#define ARRAY_GROWTH_FACTOR 2

void*  array_end(const array_t* self);
size_t array_offset(const array_t* self, size_t count);
