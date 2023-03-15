# Find packages
find_package(fmt REQUIRED)

if(${${PROJECT_NAME}_BUILD_UNITTEST})
    find_package(GTest REQUIRED)
endif()

# Link libraries
set(PROJECT_LINK_LIBS
    fmt::fmt)
set(PROJECT_TEST_LINK_LIBS
    ${PROJECT_LINK_LIBS}
    ${PROJECT_NAME_LOWERCASE}
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main)
set(PROJECT_EXAMPLE_LINK_LIBS
    ${PROJECT_LINK_LIBS}
    ${PROJECT_NAME_LOWERCASE})

# Thirdparty include directories
set(PROJECT_THIRDPARTY_INC_DIRS
    ${CONAN_INCLUDE_DIRS})
set(PROJECT_TEST_THIRDPARTY_INC_DIRS
    ${CONAN_INCLUDE_DIRS})
set(PROJECT_EXAMPLE_THIRDPARTY_INC_DIRS
    ${CONAN_INCLUDE_DIRS})
