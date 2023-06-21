#pragma once

/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* Copyright 2023, SAFRAN T4DS, ALL RIGHTS RESERVED                           */
/*                                                                            */
/* @file new.c                                                                */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#define INITIAL_SIZE   16
#define REALLOC_FACTOR 2

#define MIN(i, j)      (((i) < (j)) ? (i) : (j))
#define MAX(i, j)      (((i) > (j)) ? (i) : (j))

void* array_end(array_t* self);
size_t array_offset(array_t* self, size_t count);
bool array_grow(array_t* self, size_t grow_count);