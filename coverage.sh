#!/bin/bash
set -euo pipefail

if [ $# -gt 0 ]; then
  TOOLCHAIN="$1"
else
  TOOLCHAIN='llvm'
fi


case "$TOOLCHAIN" in
  llvm)
    export CC='clang'
    export CXX='clang++'
    export CFLAGS='-fprofile-instr-generate -fcoverage-mapping'
    ;;
  gcc)
    export CC='gcc'
    export CXX='g++'
    export CFLAGS='--coverage'
    ;;
  *) exit 1;;
esac
export CXXFLAGS="$CFLAGS"
export CPPFLAGS='-DLOG_LEVEL=LOG_LEVEL_NONE'

make fclean
make -C test fclean

make static -j "$(nproc)"
make -C test build -j "$(nproc)"

LLVM_PROFILE_FILE='test.profraw' ./test/test_libo2s.exe

LCOV_INFO='lcov.info'
case "$TOOLCHAIN" in
  llvm)
    PROFDATA='coverage.profdata'
    llvm-profdata merge -sparse ./*.profraw -o "$PROFDATA"
    rm ./*.profraw
    llvm-cov export -format lcov -instr-profile "$PROFDATA" -object libo2s.a > "$LCOV_INFO"
    ;;
  gcc)
    lcov --no-external --capture --directory . --output-file "$LCOV_INFO"
    ;;
esac

HTML_DIR='generated_html'
genhtml --output-directory "$HTML_DIR" "$LCOV_INFO"
xdg-open "$HTML_DIR/index.html" 2>/dev/null
