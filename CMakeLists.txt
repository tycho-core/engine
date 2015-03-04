cmake_minimum_required (VERSION 2.8)

include_directories("${CMAKE_SOURCE_DIR}/lib/3rdparty/")

set(link_libs "")

# TODO : why does it link to d3dx??
if(ty_platform MATCHES "pc")
    include_directories("${CMAKE_SOURCE_DIR}/3rdparty/pc/dx9")
    link_directories("${CMAKE_SOURCE_DIR}/3rdparty/pc/dx9/lib")
endif()

tycho_add_library(engine "tycore;tygraphics;tyslang;${link_libs}" "libs")



