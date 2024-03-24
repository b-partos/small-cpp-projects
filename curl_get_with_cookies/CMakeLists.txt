set(SOURCES main.cpp)

add_executable(curl_get_with_cookies ${SOURCES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_compile_definitions(curl_get_with_cookies PRIVATE CURL_STATICLIB)
target_include_directories(curl_get_with_cookies PRIVATE ${CURL_INCLUDES})
target_link_directories(curl_get_with_cookies PRIVATE ${CURL_RELEASE_LIB_DIRS})
target_link_libraries(curl_get_with_cookies PRIVATE 
  curl 
  ssl 
  crypto 
  Wldap32 # For LDAP
  Crypt32 # For Crypto and Schannel
  Normaliz # For IDN
  ssh2
  z # For Zlib
  zstd
  brotlidec
  nghttp2
  idn2 # If you have libidn2 installed
  psl # If you have libpsl installed
  Ws2_32
  Bcrypt # For BCryptGenRandom
  brotlicommon # For Brotli common functions
  unistring # For Unicode and internationalization functions
  iconv # For character set conversion functions
) 