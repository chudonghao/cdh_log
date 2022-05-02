if (TARGET cdhlog)
  return()
endif ()

set(cdhlog_FOUND NO)
set(_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../include)
set(_LIBRARY_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../lib)

# find cdhlog.h
find_file(
  cdhlog_HEADER
  cdhlog.h
  HINTS
  ${_INCLUDE_DIR}
)

# find cdhlog
find_library(
  cdhlog_LIBRARY
  cdhlog
  HINTS
  ${_LIBRARY_DIR}
)

if (NOT EXISTS "${cdhlog_HEADER}" OR NOT EXISTS "${cdhlog_LIBRARY}")
  return()
endif ()

get_filename_component(cdhlog_HEADER_DIR ${cdhlog_HEADER} DIRECTORY)
get_filename_component(cdhlog_LIBRARY_DIR ${cdhlog_LIBRARY} DIRECTORY)
message(${cdhlog_HEADER_DIR})
message(${cdhlog_LIBRARY_DIR})

# target cdhlog
add_library(cdhlog UNKNOWN IMPORTED)
set_property(TARGET cdhlog PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${cdhlog_HEADER_DIR})
set_property(TARGET cdhlog PROPERTY IMPORTED_LOCATION ${cdhlog_LIBRARY})
set_property(TARGET cdhlog PROPERTY IMPORTED_LOCATION_RELEASE ${cdhlog_LIBRARY})
set_property(TARGET cdhlog PROPERTY IMPORTED_LOCATION_DEBUG ${cdhlog_LIBRARY})

# output var
set(cdhlog_FOUND YES)
set(cdhlog_INCLUDE_DIRS ${cdhlog_HEADER_DIR})
set(cdhlog_LIBRARY_DIRS ${cdhlog_LIBRARY_DIR})
