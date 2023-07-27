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
/* @file string.h                                                             */
/* @author Hugo FOLCHER                                                       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

typedef array_t string_t;

string_t        string_new(void);
void            string_clear(string_t* self);

bool            string_append_char(string_t* self, char element);
bool            string_append_cstring(string_t* self, char* cstring, size_t length);
bool            string_append(string_t* self, string_t* other);

bool            string_pop(string_t* self, char* destination);
bool            string_pop_n(string_t* self, char* destination, size_t count);

char            string_get(string_t* self, size_t index);
char*           string_at(string_t* self, size_t index);
bool            string_is_empty(string_t* self);

bool            string_reserve(string_t* self, size_t count);
bool            string_trim(string_t* self);
