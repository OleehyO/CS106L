
# ========================    预先进行设置的配置    ======================== #

cmake_minimum_required(VERSION 3.10) # 设置CMake最低版本要求

set(CMAKE_C_COMPILER "clang")  
set(CMAKE_CXX_COMPILER "clang++")

# 使用project初始化项目时，CMake会使用到VERSION，CMAK_{C,CXX}_COMPLIER，CMAKE_TOOLCHAIN_FILE
#+等变量，因此这些变量必须要project初始化前进行设置


# ===========================    主体代码部分    ========================== #

# 初始化项目并设置语言
project(project_name LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# debug模式下启用AddressSanitizer
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

# 在没有指定构建模式时，指定为Release模式(不会生成调试信息)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()


project (hashmap_implementation)

add_executable(main 
    ./main.cpp
)
