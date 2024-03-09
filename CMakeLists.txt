cmake_minimum_required(VERSION 3.5)

# The config file contains the installation paths
include(${CMAKE_CURRENT_SOURCE_DIR}/../Config.cmake)

include(wxWidgets.cmake)
include(boost.cmake)

set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)

project(wx_widgets_test_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This must be declared before the subdirectories
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libstdc++")

add_subdirectory(wx_hello_world)
add_subdirectory(boost_object_to_json)
add_subdirectory(boost_filesystem_example)


