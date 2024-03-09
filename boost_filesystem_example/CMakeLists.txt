set(SOURCES main.cpp)

add_executable(boost_filesystem_example ${SOURCES})

target_include_directories(boost_filesystem_example PRIVATE ${BOOST_RELEASE_INCLUDES})
target_link_directories(boost_filesystem_example PRIVATE ${BOOST_RELEASE_LIB_DIRS})

target_link_libraries(boost_filesystem_example PRIVATE 
  boost_atomic-mgw13-mt-s-x64-1_84
  boost_filesystem-mgw13-mt-s-x64-1_84
  boost_system-mgw13-mt-s-x64-1_84
)



