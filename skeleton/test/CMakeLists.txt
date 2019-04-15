set(TEST_SOURCE_FILES test_main.cpp
                      test_int.cpp)

# Create target names
string(REPLACE ".cpp" "" BASENAMES_TEST_FILE "${TEST_SOURCE_FILES}")
foreach(name ${BASENAMES_TEST_FILE})
    message(STATUS ${name})
    add_executable(${name} ${name}.cpp ../src/log.cpp)
    target_include_directories(${name} PRIVATE ../include)
    target_link_libraries(${name} ${CMAKE_THREAD_LIBS_INIT} )
    add_test(NAME ${name} COMMAND ${name} -o report.xml -r junit)
endforeach()
