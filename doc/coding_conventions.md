# Coding Conventions

## Including headers

### Quote or chevron ?

In C, there is two ways to include a header :

```C
#include "header.h"
#include <header.h>
```

There is one technical difference :
only the inclusion with `"` searches for the header in the same directory as the current file
(without the need to add a `-I` compiler flag or edit an environment variable).

So in the case of a private header, i.e. one in the `src` folder alongside the sources (as opposed to one in the `include` folder), there is a technical reason to use `"` to include :

```C
#include "private.h"
```

The rest of the time, either way of including could technically be used.
So the following rule is an arbitrary convention :

> When including a header, use `"` if that header is in the same git repository, else use `<>`

So that means that when in `o2s/string.h` we are including `o2s/array.h` and `stddef.h`, we write:

```C
#include "o2s/array.h"

#include <stddef.h>
```

### Order

While any inclusion order would do, going from most to least specific has an advantage:
If someone were to write a header like `o2s/array.h`, using the type `bool` but forgetting to include `stdbool.h`,
then if all source files that include `o2s/array.h` also include (directly or no) `stdbool.h` above, then the omission will go unnoticed.

So the convention here is something like :

```C
/* Source specific header */
#include "private.h"

/* Project specific public headers */
#include "o2s/deque.h"
#include "o2s/string.h"

/* Linux specific headers */
#include <fcntl.h>
#include <termios.h>

/* Standard C headers */
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
```

Within a given group, lines are sorted alphabetically.
