cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME exam)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)

# Options
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors." ON)
option(ENABLE_SANITIZERS "Use sanitizers to detect errors." OFF)
option(ENABLE_CONAN "Use Conan as a package manager." OFF)
option(ENABLE_PVS_STUDIO "Check using command-line PVS-Studio." ON)

# Set output directories
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Warnings
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror -Werror=vla)
endif()
# Include fixed CMake configuration
include(../cmake/config.cmake)

# Include headers
include_directories(inc)
include_directories(${readline_INCLUDE_DIR})

# Add external packages
find_package(Boost 1.71.0 COMPONENTS mpi system program_options REQUIRED)
set(Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
set(Boost_USE_MULTITHREAD ON)  # enable maltreating
include_directories(${Boost_INCLUDE_DIR})

# Project source compilation
add_executable(${PROJECT_NAME} src/main.cpp src/master.cpp src/slave.cpp src/options_parser.cpp src/inner_commands.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} readline)


# Sanitizers configuration
if (ENABLE_SANITIZERS)
    set(SANITIZE_UNDEFINED ON)
    # Only one of Memory, Address, or Thread sanitizers is applicable at the time
    set(SANITIZE_MEMORY ON)
    #    set(SANITIZE_ADDRESS ON)
    #    set(SANITIZE_THREAD ON)
    find_package(Sanitizers)

    # CMake targets to which apply sanitizers
    add_sanitizers(${PROJECT_NAME})
endif ()

#####################################
# create own target for library
if(ENABLE_PVS_STUDIO)
    include(../cmake/PVS-Studio.cmake)
    SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    # create own target for library
    pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
            ANALYZE ${PROJECT_NAME}
            OUTPUT FORMAT errorfile
            MODE GA:1,2,3 OP:1,2,3 GA:1,2,3 OP:1,2,3 64:1,2,3 CS:1,2,3 MISRA:1,2,3
            LOG target_${PROJECT_NAME}.err)
else()
    message("Consider checking using PVS-Studio with `cmake -DENABLE_PVS_STUDIO=ON <.....>` or Windows GUI application.")
endif()
#####################################
