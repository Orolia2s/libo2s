# Lib O2S

Reliant datastructure library for C.

The [include](include) folder contains the public interface, while the [src](src) folder contains the implementation.

## Create a local conan package

```bash
conan create .
```

__requires__ conan

## Test and display coverage in the browser

```bash
bash coverage.sh
```

__requires__ gcc, g++, gcov, lcov (compatible versions !)
