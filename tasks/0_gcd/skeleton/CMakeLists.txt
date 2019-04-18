add_executable(skeleton
  src/main.cpp
  src/gcd.cpp
)

target_include_directories(skeleton PRIVATE include/)
add_subdirectory(test)
