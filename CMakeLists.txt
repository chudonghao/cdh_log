cmake_minimum_required(VERSION 3.21)
project(cdhlog)

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
target_link_libraries(cdhlog INTERFACE Boost::log Boost::log_setup)

# for test
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# tests
add_subdirectory(test)

# install
set_property(TARGET cdhlog PROPERTY PUBLIC_HEADER cdhlog.h)
install(
  TARGETS
  cdhlog
  PUBLIC_HEADER
  RUNTIME
  LIBRARY
  ARCHIVE
)
install(
  FILES
  cmake/cdhlog-config.cmake
  DESTINATION
  ${CMAKE_INSTALL_PREFIX}/lib/cmake/cdhlog
)
