set(SOURCES main.cpp html_parser.cpp)

add_executable(libxml2_example ${SOURCES})


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Oxygen_Wikipedia.htm
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# LIBXML_STATIC must be set or the linker will try to link against the shared library
target_compile_definitions(libxml2_example PRIVATE LIBXML_STATIC)
target_include_directories(libxml2_example PRIVATE ${XML2_INCLUDES})
target_link_directories(libxml2_example PRIVATE ${XML2_RELEASE_LIB_DIRS})
target_link_libraries(libxml2_example PRIVATE xml2 z lzma iconv ws2_32)


