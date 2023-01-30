cmake_minimum_required(VERSION 3.16)

enable_testing()
project(Mausukira VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project modules
add_subdirectory(dependencies)
add_subdirectory(MausukiraApp)
add_subdirectory(MauskiraTests)