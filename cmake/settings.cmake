# Options
option(${PROJECT_NAME}_BUILD_UNITTEST "Build unittest" ON)
option(${PROJECT_NAME}_BUILD_EXAMPLES "Build examples" ON)
option(${PROJECT_NAME}_ENABLE_CCACHE "Enable the usage of Ccache, in order to speed up rebuild times." ON)
option(${PROJECT_NAME}_ENABLE_LTO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)." OFF)
option(${PROJECT_NAME}_ENABLE_SAN "Enable Sanitizer" OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Export all symbols when building a shared library
if(BUILD_SHARED_LIBS)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
endif()

# Build/Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# LTO
if(${${PROJECT_NAME}_ENABLE_LTO})
    message(STATUS "LTO enabled")
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(SEND_ERROR "IPO is not supported: ${output}.")
    endif()
endif()

# Sanitizer
if(${${PROJECT_NAME}_ENABLE_SAN})
    message(STATUS "Sanitizer enabled")
    add_compile_options(-fsanitize=address,leak,undefined)
    add_link_options(-fsanitize=address,leak,undefined)
endif()

# ccache
if(${${PROJECT_NAME}_ENABLE_CCACHE})
    message(STATUS "ccache enabled")
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif()
endif()

# Print settings
message(STATUS "${PROJECT_NAME}: v${PROJECT_VERSION}")
message(STATUS "C++: ${CMAKE_CXX_COMPILER}-${PROJECT_CXX_VERSION}")
message(STATUS "Shared lib: ${BUILD_SHARED_LIBS}")
message(STATUS "Build: ${CMAKE_BUILD_TYPE}")
message(STATUS "CCACHE: ${${PROJECT_NAME}_ENABLE_CCACHE}")
message(STATUS "LTO: ${${PROJECT_NAME}_ENABLE_LTO}")
message(STATUS "SANITIZER: ${${PROJECT_NAME}_ENABLE_SAN}")
