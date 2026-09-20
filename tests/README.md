# Compile checks and retained cases

Enable compile checks with `GREVIR_BUILD_COMPILE_CHECKS=ON`.
The native build compiles each installed header by itself and the explicit
`native_compile.cpp` template users. Grevir Base also compiles the legacy tuple
static assertions extracted from its public header.

Other `.cpp` files are retained historical cases with relocated production
includes. They are **not built or run yet**: their old `setl_test_framework.h` and
`assert_that.h` dependencies belong to the future test-support extraction.
Porting those cases and adding a runtime harness are separate work.
