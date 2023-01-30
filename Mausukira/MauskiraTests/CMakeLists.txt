cmake_minimum_required(VERSION 3.16)

project(MauskiraTests LANGUAGES CXX)
include_directories(../MausukiraApp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

# Download and unpack googletest at configure time
configure_file("CMakeLists.txt.in" "${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt")
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
        )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
        )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build"
        )

# The gtest/gmock targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we
# have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include"
            )
endif ()


add_executable(MauskiraTests
        main.cpp
        ut/SampleTest.cpp
        )

target_link_libraries(MauskiraTests
        PRIVATE
        sfml-graphics
        sfml-system
        sfml-window
        EnTT::EnTT
        jsoncpp_lib
        poly2tri
        tgui
        )

if (WIN32)
    add_custom_command(TARGET MauskiraTests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:MauskiraTests>)
endif ()

target_link_libraries(MauskiraTests PRIVATE MausukiraSrc)
target_link_libraries(MauskiraTests PRIVATE gtest gtest_main)
target_link_libraries(MauskiraTests PRIVATE gmock gmock_main)