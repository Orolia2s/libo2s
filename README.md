# Lib O2S

Reliable datastructure library for C.

The [include](include) folder contains the public interface, while the [src](src) folder contains the implementation.

## Data structures

```mermaid
classDiagram
  class A["Array"] {
    memory
    push_back()
    pop_back()
  }
  class S["String"] {
  }
  class D["Deque"] {
    memory
    push_back()
    push_front()
    pop_back()
    pop_front()
  }
  class Q["Queue"] {
    push()
    pop()
  }
  class T["Stack"] {
    push()
    pop()
  }
  A <|-- S
  D <|-- T
  D <|-- Q
```

### Primary
- [Array](https://orolia2s.pages.orolia.com/libo2s/array_8h.html): Dynamic array
- [Deque](https://orolia2s.pages.orolia.com/libo2s/deque_8h.html): Double-ended queue

### Secondary
- [String](https://orolia2s.pages.orolia.com/libo2s/string_8h.html): Dynamic character array
- [Queue](https://orolia2s.pages.orolia.com/libo2s/queue_8h.html): FIFO
- [Stack](https://orolia2s.pages.orolia.com/libo2s/stack_8h.html): LIFO

## Input/Output
```mermaid
classDiagram
  class I["input stream"] {
    buffer
    accumulate(count)
  }
  class S["string input stream"] {
  }
  class F["file input stream"] {
    file descriptor
  }
  I <|-- S
  I <|-- F
```

- [File Input Stream](https://orolia2s.pages.orolia.com/libo2s/file__input__stream_8h.html): Buffered file reader
- [String Input Stream](https://orolia2s.pages.orolia.com/libo2s/string__input__stream_8h.html): Interchangable with a file input stream, to mock / test
- [Serial Ports](https://orolia2s.pages.orolia.com/libo2s/serial_8h.html): Configure and read from serial ports

## Utilities
- [Logging functions](https://orolia2s.pages.orolia.com/libo2s/log_8h.html)
- [String conversions](https://orolia2s.pages.orolia.com/libo2s/to__string_8h.html)
- [Useful Macros](https://orolia2s.pages.orolia.com/libo2s/preprocessing_8h.html)
- [Timers](https://orolia2s.pages.orolia.com/libo2s/timer_8h.html)
- [Mutex](https://orolia2s.pages.orolia.com/libo2s/mutex_8h.html)

# Usage

## Use in your project

Add the dependency in your `build.zig.zon` by running the following command:
```shell
zig fetch --save git+https://github.com/Orolia2s/libo2s#master
```

Then, in your `build.zig`:
```zig
const libo2s = b.dependency("libo2s", { .target = target, .optimize = optimize }).artifact("o2s");

// wherever needed:
exe.linkLibrary(libo2s);
```

## Build

requires [zig](https://ziglang.org/download/) >= 0.14.0

```shell
zig build
```

## Test

```shell
zig build test
```

## Generate documentation

requires [doxygen](https://www.doxygen.nl/download.html)

```shell
zig build doc
open doc/html/index.html
```
