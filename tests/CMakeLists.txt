# Test Project
project(${CMAKE_PROJECT_NAME}Tests LANGUAGES CXX)

# Settigns
include(CTest)
include(GoogleTest)
file(GLOB_RECURSE test_sources "${CMAKE_SOURCE_DIR}/tests/src/*.cpp")
file(GLOB_RECURSE test_headers "${CMAKE_SOURCE_DIR}/tests/src/*.cpp")

# Build
foreach(file ${test_sources})
    string(REGEX REPLACE "(.*/)([a-zA-Z0-9_ ]+)(\.cpp)" "\\2" test_name ${file})
    message(STATUS "${file} ${test_name}")
    add_executable(${test_name} ${file} ${test_headers})

    target_compile_options(${test_name} PUBLIC ${PROJECT_WARNINGS})
    target_include_directories(${test_name}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests/include>
        PRIVATE
            ${CMAKE_SOURCE_DIR}/tests/src)
    target_include_directories(${test_name}
        SYSTEM PUBLIC
            ${PROJECT_TEST_THIRDPARTY_INC_DIRS})
    target_link_libraries(${test_name}
        PRIVATE
            ${PROJECT_TEST_LINK_LIBS})

    set_target_properties(
        ${test_name}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")

    add_test(
        NAME ${test_name}
        COMMAND ${test_name})
endforeach()
