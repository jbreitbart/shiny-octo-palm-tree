add_executable(skeleton
  src/main.cpp
  src/log.cpp
)

target_include_directories(skeleton PRIVATE include/)

add_subdirectory(test)
