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
/* @file preprocessing.h                                                      */
/* @author Antoine GAGNIERE                                                   */
/*                                                                            */
/* ************************************************************************** */

/** Changes token type to string literal */
#define LIBO2S_PREPRO_STRING_DIRECT(EXPRESSION) #EXPRESSION

/** Create a string literal from the evaluation of its argument */
#define LIBO2S_PREPRO_STRING(EXPRESSION)        LIBO2S_PREPRO_STRING_DIRECT(EXPRESSION)
