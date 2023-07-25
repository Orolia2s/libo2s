#!/bin/bash
set -euo pipefail
IFS=$'\n\t'
# Strict mode : abort on failures

make fclean
make -C test clean

CFLAGS="-fprofile-arcs -ftest-coverage" make static
CXXFLAGS="-fprofile-arcs -ftest-coverage" make -C test conan_build

./test/test_libo2s.exe

lcov --no-external --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory generated_html

xdg-open generated_html/index.html
