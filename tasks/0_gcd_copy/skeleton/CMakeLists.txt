add_executable(gcd_skeleton_copy
  src/main.cpp
  src/gcd.cpp
)

target_include_directories(gcd_skeleton_copy PRIVATE include/)
add_subdirectory(test)
