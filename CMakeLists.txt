cmake_minimum_required(VERSION 3.21)
project(cdhlog VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Boost
find_package(Boost REQUIRED COMPONENTS log log_setup)
include_directories(${Boost_INCLUDE_DIRS})

# cdhlog
set(
  SRCS
  cdhlog.hpp
  cdhlog_setup.hpp
)
add_library(cdhlog INTERFACE ${SRCS})
target_include_directories(cdhlog INTERFACE $<INSTALL_INTERFACE:include>)
target_link_libraries(cdhlog INTERFACE Boost::log Boost::log_setup)
set_property(TARGET cdhlog PROPERTY PUBLIC_HEADER cdhlog.hpp cdhlog_setup.hpp)

# for test
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# tests
add_subdirectory(test)

# install
install(
  TARGETS cdhlog
  EXPORT cdhlog-targets
  PUBLIC_HEADER DESTINATION include
)

install(
  EXPORT cdhlog-targets
  FILE cdhlog-targets.cmake
  DESTINATION lib/cmake/cdhlog
)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/cdhlog-config.cmake"
  INSTALL_DESTINATION "lib/cmake/cdhlog"
  NO_SET_AND_CHECK_MACRO
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/cdhlog-config-version.cmake"
  VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/cdhlog-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cdhlog-config-version.cmake
  DESTINATION lib/cmake/cdhlog
  )
