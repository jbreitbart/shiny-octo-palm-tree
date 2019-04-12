add_executable(skeleton
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/log.cpp
)

target_include_directories(skeleton PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_subdirectory(test)
