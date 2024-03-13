set(SOURCES main.cpp)

add_executable(wx_mupdf_test_1 ${SOURCES})

target_include_directories(wx_mupdf_test_1 PRIVATE ${WX_WIDGET_INCLUDES})
target_link_directories(wx_mupdf_test_1 PRIVATE ${WX_WIDGET_LIB_DIRS})
target_link_libraries(wx_mupdf_test_1 PRIVATE ${WX_WIDGET_LIBS})
# Libraries needed to link against muPDF
target_link_libraries(wx_mupdf_test_1 PRIVATE mupdf jpeg z jbig jbig2dec openjp2 freetype harfbuzz png graphite2 openjp2.dll bz2 brotlidec brotlicommon gumbo mupdf-third)
target_link_libraries(wx_mupdf_test_1 PRIVATE C:/msys64/ucrt64/bin/libopenjp2-7.dll) # This was dinamically linked to the muPDF lib downloaded
target_link_libraries(wx_mupdf_test_1 PRIVATE rpcrt4) # This should provide the UUID function



