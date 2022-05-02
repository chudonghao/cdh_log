
add_executable(
  ${PROJECT_NAME}_test
  test.cpp
)
target_link_libraries(${PROJECT_NAME}_test cdhlog)
