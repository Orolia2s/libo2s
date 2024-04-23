/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/**
* @copyright 2024, SAFRAN T4DS, ALL RIGHTS RESERVED
* @file hashes.c
* @author Antoine GAGNIERE
*/
/* ************************************************************************** */

#include "o2s/private_prepro.h" // FNV1A_*
#include "o2s/string.h"

/** Fowler–Noll–Vo hash function, in 32 bits */
uint32_t cstring_fnv1a_32(const char* cstring, size_t length)
{
	uint32_t c;
	uint32_t hash;

	hash = FNV1A_0();
	while (length --> 0)
	{
		c = (unsigned char)*cstring++;
		hash ^= c;
		hash *= FNV1A_F;
	}
	return hash;
}

/** Fowler–Noll–Vo hash function, in 32 bits */
uint32_t string_fnv1a_32(const string_t* self)
{
	return cstring_fnv1a_32(string_get(self, 0), string_length(self));
}
