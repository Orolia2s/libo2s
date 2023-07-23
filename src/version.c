#include "o2s/version.h"

#include "o2s/preprocessing.h"

/** The libO2S version as a null-terminated string. */
const char* libo2s_version_cstr()
{
	return LIBO2S_PREPRO_STRING(LIBO2S_VERSION);
}
