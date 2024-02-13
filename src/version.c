/* ************************************************************************** */
/*      ____    _    _____ ____     _    _   _   _____ _  _   ____  ____      */
/*     / ___|  / \  |  ___|  _ \   / \  | \ | | |_   _| || | |  _ \/ ___|     */
/*     \___ \ / _ \ | |_  | |_) | / _ \ |  \| |   | | | || |_| | | \___ \     */
/*      ___) / ___ \|  _| |  _ < / ___ \| |\  |   | | |__   _| |_| |___) |    */
/*     |____/_/   \_|_|   |_| \_/_/   \_|_| \_|   |_|    |_| |____/|____/     */
/*                                                                            */
/* ************************************************************************** */

#include "o2s/version.h"

#include "o2s/preprocessing.h"

/** The libO2S version as a null-terminated string. */
const char* libo2s_version_cstring(void)
{
	return LIBO2S_PREPRO_STRING(LIBO2S_VERSION);
}

/** The libO2S version as a dynamic string. */
string_t libo2s_version_string(void)
{
	return string_from_literal(LIBO2S_PREPRO_STRING(LIBO2S_VERSION));
}
