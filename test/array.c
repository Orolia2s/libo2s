#include "o2s/array.h"

#include <libunit.h>

#define ARRAY_condition(name, ...)                                          \
    ({                                                                      \
        bool    result     = true;                                          \
        array_t tested     = Array(int);                                    \
        int     elements[] = {__VA_ARGS__};                                 \
        size_t  length     = sizeof(elements) / sizeof(*elements);          \
        for (int i = 0; i < length; i++)                                    \
        {                                                                   \
            array_push_back(&tested, elements + i);                         \
            result = result && (*(int*)array_last(&tested) == elements[i]); \
        }                                                                   \
        result = result && (*(int*)array_first(&tested) == elements[0]);    \
        result;                                                             \
    })

TEST_SECTION(array_push_back, extract_name, ARRAY_condition,
	(single, 42),
    (five, 0, 1, 2, 3, 4),
    (negative, 10, -20, 30, -40, 50, -60),
    (ten, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
)
