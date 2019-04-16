add_executable(skeleton
  src/main.cpp
)

target_include_directories(skeleton PRIVATE include/)

add_subdirectory(test)
