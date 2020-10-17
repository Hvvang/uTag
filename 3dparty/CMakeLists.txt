cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_EXTENSIONS OFF)
set(TAGLIB_INCLUDE_DIR "./taglib/taglib/taglib")
set(TAGLIB_LIBRARY_DIR "./taglib/build/lib")

link_directories(TAGLIB_LIBRARY_DIR)
include_directories(TAGLIB_INCLUDE_DIR)

add_subdirectory(taglib)
