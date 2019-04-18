set(TEST_SOURCE_FILES test_main.cpp
                      test_gcd.cpp)

# Create target names
string(REPLACE ".cpp" "" BASENAMES_TEST_FILE "${TEST_SOURCE_FILES}")
foreach(name ${BASENAMES_TEST_FILE})
    message(STATUS ${name})
    add_executable(${name} ${name}.cpp ../src/add.cpp)
    target_include_directories(${name} PRIVATE ../include)
#    target_compile_options(${name} PRIVATE --coverage)
#    target_link_options(${name} PRIVATE --coverage)
    add_test(NAME ${name} COMMAND ${name} -o report.xml -r junit)
endforeach()
