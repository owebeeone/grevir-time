if(NOT COMMAND catch_discover_tests)
  find_package(grevir-test-support CONFIG REQUIRED)
endif()
add_executable(grevir_time_runtime time_test.cpp units_test.cpp)
target_link_libraries(grevir_time_runtime PRIVATE grevir::time Catch2::Catch2WithMain)
set_target_properties(grevir_time_runtime PROPERTIES CXX_EXTENSIONS OFF)
catch_discover_tests(grevir_time_runtime TEST_PREFIX "time."
  PROPERTIES LABELS "time" TIMEOUT 10)
