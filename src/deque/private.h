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
/* @file private.h                                                            */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

size_t deque_offset(const deque_t* self, size_t count);
size_t deque_room(const deque_t* self);
size_t deque_right_distance(const deque_t* self, size_t index);
size_t deque_index_shift(const deque_t* self, size_t index, int shift);

bool   deque_front_shift(deque_t* self, int shift);
bool   deque_back_shift(deque_t* self, int shift);
void*  deque_get_element_from_index(deque_t* self, size_t index);
