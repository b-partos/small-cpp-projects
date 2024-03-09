

include(${CMAKE_CURRENT_LIST_DIR}/../Config.cmake)

# Specify the target operating system
set(CMAKE_SYSTEM_NAME Windows)

# Specify the target processor architecture
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Set the compilers
set(CMAKE_C_COMPILER "${MSYS2_UCRT64_ROOT}/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "${MSYS2_UCRT64_ROOT}/bin/g++.exe")

# Set the build tool
set(CMAKE_MAKE_PROGRAM "${MSYS2_UCRT64_ROOT}/bin/ninja.exe")

# Specify additional compiler flags if needed
# For example:
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")