
# The config file contains the installation paths
include(${CMAKE_CURRENT_SOURCE_DIR}/../Config.cmake)

set(WX_WIDGET_INCLUDES
    ${WX_WIDGET_INSTALL_ROOT}/include/wx-3.2
    ${WX_WIDGET_INSTALL_ROOT}/lib/wx/include/msw-unicode-static-3.2
)

set(WX_WIDGET_LIB_DIRS
    ${WX_WIDGET_INSTALL_ROOT}/lib
)

set(WX_WIDGET_LIBS
    wx_mswu_xrc-3.2
    wx_mswu_qa-3.2
    wx_baseu_net-3.2
    wx_mswu_html-3.2
    wx_mswu_core-3.2
    wx_baseu_xml-3.2
    wx_baseu-3.2
    wxtiff-3.2
    wxjpeg-3.2
    wxpng-3.2
    wxregexu-3.2
    wxscintilla-3.2
    wxexpat-3.2
    wxzlib-3.2
    rpcrt4
    oleaut32
    ole32
    uuid
    uxtheme
    winspool
    winmm
    shell32
    shlwapi
    comctl32
    comdlg32
    advapi32
    version
    ws2_32
    gdi32
    oleacc
    winhttp
)