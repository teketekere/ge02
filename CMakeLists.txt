cmake_minimum_required(VERSION 3.21)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project details
project(
  "GE"
  VERSION 0.1.0
  LANGUAGES CXX)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)

# Settings
include(cmake/settings.cmake)
include(cmake/libs.cmake)
include(cmake/compile_warnings.cmake)
include(cmake/sources.cmake)

# Build
add_library(${PROJECT_NAME_LOWERCASE} ${sources} ${headers})
target_compile_options(${PROJECT_NAME_LOWERCASE} PUBLIC ${PROJECT_WARNINGS})
target_include_directories(${PROJECT_NAME_LOWERCASE}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME_LOWERCASE}
    SYSTEM PUBLIC
        ${PROJECT_THIRDPARTY_INC_DIRS}
)
target_link_libraries(${PROJECT_NAME_LOWERCASE} PRIVATE ${PROJECT_LINK_LIBS})
set_target_properties(
    ${PROJECT_NAME_LOWERCASE}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")

# Unittest
if(${PROJECT_NAME}_BUILD_UNITTEST)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

# Examples
if(${PROJECT_NAME}_BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif()
