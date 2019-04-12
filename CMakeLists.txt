cmake_minimum_required(VERSION 3.13)

########
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their definition
# and dump it in the cache along with proper documentation, otherwise set CMAKE_BUILD_TYPE
# to Debug prior to calling PROJECT()
IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()
string( TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE )
########

project (shiny-octo-palm-tree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

########
# Compiler/linker options based on the different compilers
# Intentionally set for all targets to be created later
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # Using Clang
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
  add_compile_options(-g -Ofast -march=native)
  endif()

  if ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
    add_compile_options(-g3 -O1 -Weverything)

    # enable sanitizers
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
    # choose one: memory or address
    #add_compile_options(-fsanitize=memory -fno-omit-frame-pointer)
    #add_link_options(-fsanitize=memory)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls)
    add_link_options(-fsanitize=address)

    # we are using modern c++
    add_compile_options(-Wno-c++98-compat -Wno-c++98-compat-pedantic)

    # silence warnings coming from spdlog
    add_compile_options(-Wno-padded -Wno-weak-vtables -Wno-switch-enum -Wno-exit-time-destructors -Wno-global-constructors)
  endif()

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # Using GCC
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
  add_compile_options(-g -O2 -march=native)
  endif()

  if ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
  add_compile_options(-g3 -O0 -Wall -Wextra -Wunused)
  endif()
endif()
########

include_directories(vendor/spdlog/include)
include_directories(vendor/catch2/include/)

enable_testing()
ADD_SUBDIRECTORY(skeleton)
ADD_SUBDIRECTORY(tasks)
