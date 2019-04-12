#
# BFS project build script
#
cmake_minimum_required(VERSION 3.8)

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

project (BreadthFirstSearch)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

set(HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/app/app.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/app/bfs.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/app/graph.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/app/node.h
)

set(SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/log.cpp
)

add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${HEADER_FILES}
)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

########
# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
########

########
# Compiler/linker options based on the different compilers
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # Using Clang
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -Ofast -march=native)
  endif()

  if ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g3 -O1 -Weverything)

    # enable sanitizers
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=undefined)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS -fsanitize=undefined)
    # choose one: memory or address
    #target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=memory -fno-omit-frame-pointer)
    #set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS -fsanitize=memory)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS -fsanitize=address)

    # we are using modern c++
    target_compile_options(${PROJECT_NAME} PRIVATE -Wno-c++98-compat -Wno-c++98-compat-pedantic)

    # silence warnings coming from spdlog
    target_compile_options(${PROJECT_NAME} PRIVATE -Wno-padded -Wno-weak-vtables -Wno-switch-enum -Wno-exit-time-destructors -Wno-global-constructors)
  endif()

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # Using GCC
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O2 -march=native)
  endif()

  if ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g3 -O0 -Wall -Wextra -Wunused)
  endif()

endif()
########

if ("${CMAKE_BUILD_TYPE}" STREQUAL "release")
  target_compile_definitions(${PROJECT_NAME} PRIVATE LEVELS=5)
  target_compile_definitions(${PROJECT_NAME} PRIVATE NODES=5)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE LEVELS=4)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NODES=3)
endif()

enable_testing()
add_subdirectory(test)
