set(SOURCES main.cpp)

add_executable(wx_hello_world ${SOURCES})
target_include_directories(wx_hello_world PRIVATE ${WX_WIDGET_INCLUDES})
target_link_directories(wx_hello_world PRIVATE ${WX_WIDGET_LIB_DIRS})
target_link_libraries(wx_hello_world PRIVATE ${WX_WIDGET_LIBS})



