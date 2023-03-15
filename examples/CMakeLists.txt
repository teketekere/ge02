function(configure_example_project  name)
    target_compile_options(${name} PUBLIC ${PROJECT_WARNINGS})
    target_include_directories(${name}
        PUBLIC
            ${CMAKE_SOURCE_DIR}/examples/include
        PRIVATE
            ${CMAKE_SOURCE_DIR}/examples/src)
    target_include_directories(${name}
        SYSTEM PUBLIC
            ${PROJECT_EXAMPLE_THIRDPARTY_INC_DIRS})
    target_link_libraries(${name}
        PRIVATE
            ${PROJECT_EXAMPLE_LINK_LIBS})
    set_target_properties(
        ${name}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
endfunction()

# 001
add_executable(Example001 ${CMAKE_SOURCE_DIR}/examples/src/001.cpp)
configure_example_project(Example001)
