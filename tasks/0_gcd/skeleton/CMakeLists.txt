add_executable(gcd_skeleton
  src/main.cpp
  src/gcd.cpp
)

target_include_directories(gcd_skeleton PRIVATE include/)
add_subdirectory(test)
