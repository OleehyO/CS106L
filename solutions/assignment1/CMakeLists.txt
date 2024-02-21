cmake_minimum_required(VERSION 3.10)

# 使用vcpkg来管理第三方包
set(CMAKE_TOOLCHAIN_FILE 
    "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file"
)


project(wikiracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find_package(cpr CONFIG REQUIRED PATHS "/home/lhy/code/cs106L-assignment1/vcpkg/installed/x64-linux")
find_package(cpr CONFIG REQUIRED)
option(TEST_WIKISCRAPER "Test wikiracer only" OFF)

if(TEST_WIKISCRAPER)
    message("Building Wikiscraper Test")
    add_executable(test test-wikiscraper.cpp wikiscraper.cpp error.cpp)
    target_link_libraries(test PRIVATE cpr::cpr)
else()
    message("Building Entire Project")
    add_executable(main main.cpp wikiscraper.cpp error.cpp)
    target_link_libraries(main PRIVATE cpr::cpr)
endif()

