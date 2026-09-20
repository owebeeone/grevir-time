# Grevir Time

Typed times, periods, unit conversions and interactive scaling extracted from
Ardoinus. This header-only library depends on Grevir Base. Include `<GrevirTime.h>`
or an individual `<grevir/time/...hpp>` header; the API still uses namespace `setl`.
This is a local development snapshot, not a published release.

## Native build

Install Grevir Base first, then configure this repository against that prefix:

```sh
cmake -S . -B build/native -G "Unix Makefiles" \
  -DCMAKE_CXX_COMPILER="$(xcrun --find clang++)" \
  -DCMAKE_PREFIX_PATH=/your/grevir-install \
  -DGREVIR_BUILD_COMPILE_CHECKS=ON
cmake --build build/native
cmake --install build/native --prefix /your/grevir-install
```

Consumers use `find_package(grevir-time CONFIG REQUIRED)` and link `grevir::time`.
Grevir Base is resolved as an explicit dependency, without searching sibling
checkouts. The workspace can also supply its existing `grevir::base` target.

For Arduino packaging, put both library checkouts directly under `libraries/`.
The root metadata declares `depends=Grevir Base`. Board compiler integration and
language/header capabilities remain to be validated; the current verified build
uses native Apple Clang 21 and C++23 with the standard library enabled.

## Current validation

Every public header compiles independently, as do concrete uses of unit conversion,
time arithmetic, literals and interactive scaling. Historical tests are retained
but await harness adaptation; see [tests/README.md](tests/README.md).

Algorithms are preserved during relocation. Existing literal-operator whitespace
produces Clang deprecation warnings. A known legacy issue, `TimeUnit::PICOS` and
`TimeUnit::NANOS` sharing the same enum value, also remains for a focused correctness
change. Native compilation does not establish the runtime correctness of those
algorithms or hardware behavior.

Source: [owebeeone/ardoinus](https://github.com/owebeeone/ardoinus). Its README
selects the MIT license in `LICENSE.txt`; that notice is copied unchanged here.
