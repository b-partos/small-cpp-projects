set(SOURCES main.cpp)

add_executable(boost_object_to_json ${SOURCES})

target_include_directories(boost_object_to_json PRIVATE ${BOOST_RELEASE_INCLUDES})
target_link_directories(boost_object_to_json PRIVATE ${BOOST_RELEASE_LIB_DIRS})


