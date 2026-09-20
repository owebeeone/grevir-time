# Native checks and retained tests

`GREVIR_BUILD_COMPILE_CHECKS=ON` compiles each public header independently and
concrete time, conversion, literal and scaling users.

`GREVIR_BUILD_HOST_TESTS=ON` builds the two retained test files with Catch2/CTest.
Three runtime cases cover typed arithmetic/literals, the historical conversion
matrix over nine numeric types, and unsigned 32-bit elapsed-time wraparound.
The old SetlTest/assertThat dependency is removed. Disabled historical arithmetic
experiments remain disabled; this suite does not cover every operator or unit.
No dedicated PICOS/NANOS regression was added, per the user's instruction.

For standalone builds, install Grevir Base and Grevir Test Support, and provide
Catch2 3.8.1 through an installed package or `GREVIR_CATCH2_SOURCE_DIR`. The workspace
supplies the helper automatically. Dependency fetching is disabled unless explicitly
enabled. Run `ctest --test-dir build/host --output-on-failure` after building.
