cmake_minimum_required(VERSION 3.20)
project(grevir_time VERSION 0.1.0 LANGUAGES CXX)

if(NOT TARGET grevir::base)
  find_package(grevir-base CONFIG REQUIRED)
endif()

add_library(grevir_time INTERFACE)
add_library(grevir::time ALIAS grevir_time)
set_target_properties(grevir_time PROPERTIES EXPORT_NAME time)
target_compile_features(grevir_time INTERFACE cxx_std_23)
target_link_libraries(grevir_time INTERFACE grevir::base)
target_include_directories(grevir_time INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>)

include(GNUInstallDirs)
install(TARGETS grevir_time EXPORT GrevirTimeTargets)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING
  PATTERN "*.hpp" PATTERN "*.h")
install(EXPORT GrevirTimeTargets NAMESPACE grevir::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/grevir-time)
install(FILES cmake/grevir-time-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/grevir-time)
install(FILES LICENSE.txt DESTINATION ${CMAKE_INSTALL_DATADIR}/grevir-time)

option(GREVIR_BUILD_COMPILE_CHECKS "Compile native headers and template users" OFF)
option(GREVIR_BUILD_HOST_TESTS "Run deterministic native behavior tests" OFF)
if(GREVIR_BUILD_HOST_TESTS)
  enable_testing()
endif()
if(GREVIR_BUILD_COMPILE_CHECKS OR GREVIR_BUILD_HOST_TESTS)
  add_subdirectory(tests)
endif()
