cmake_minimum_required(VERSION 3.2)
project(goonPhysics
    VERSION 0.1.0
    LANGUAGES C)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add all of our source files
file(GLOB FILES src/*.c)
file(GLOB goon_public_header "${goonPhysics_SOURCE_DIR}/include/GoonPhysics/*.h")

# Build a win32 bundle when building on win, and macos when building on ios,  Remove macosbundle as its easier to copy the files and debug #Remove win32 as couldn't build with sdl2
add_library(goonPhysics
    STATIC
    ${FILES})
set_property(TARGET goon_sound PROPERTY C_STANDARD 99)

find_package(PkgConfig)

# For Debug, print aout all variables.
if(DEBUG_VARS)
    get_cmake_property(_variableNames VARIABLES)
    list(SORT _variableNames)

    foreach(_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif(DEBUG_VARS)

target_include_directories(goon_sound
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_options(goon_sound PUBLIC -std=c99 -Wall -pedantic)

install(TARGETS goonPhysics ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
install(FILES ${goon_public_header} DESTINATION include/chipmunk)