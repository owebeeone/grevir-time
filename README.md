# Grevir Time

**Public API:** [Grevir Time](https://github.com/owebeeone/grevir-wz/blob/main/docs/api/time.md).
See [installation](https://github.com/owebeeone/grevir-wz/blob/main/docs/install.md) and
[supported platforms](https://github.com/owebeeone/grevir-wz/blob/main/docs/supported.md).
The workspace `/docs` is the current user-facing contract; development
checkpoints below are historical.

Typed time values, periods, conversions and interactive scaling.

## Development record (historical)

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
time arithmetic, literals and interactive scaling. Both retained test files now
build with Catch2/CTest, providing four passing cases for arithmetic/literals,
legacy conversions, unsigned clock wraparound and scalar division; see [tests/README.md](tests/README.md).

Existing literal-operator whitespace produces Clang deprecation warnings.
On 21 September 2026, the `PICOS`/`NANOS` enum collision was corrected using
sequential values and an explicit `JIFFY = CENTIS` alias. Values from `NANOS`
onward increase by one. No dedicated test was added for that correction, as
requested; the subsequent foundation/peripheral build and retained runtime suite
pass with the updated header, and its ledger hash is current.

`Period::operator/` now divides by its scalar operand, preserving the period
storage type and units. Its regression reproduced `12 / 3 == 36` before the fix;
signed/unsigned, fractional and integer-truncation cases now pass. Coverage remains
partial, and hardware behavior remains unvalidated.

Source: [owebeeone/ardoinus](https://github.com/owebeeone/ardoinus). Its README
selects the MIT license in `LICENSE.txt`; that notice is copied unchanged here.
