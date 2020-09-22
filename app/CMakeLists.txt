cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_library(TAGLIB taglib)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(../3dparty/taglib/taglib/)
include_directories(../3dparty/taglib/taglib/asf/)
include_directories(../3dparty/taglib/taglib/mpeg/)
include_directories(../3dparty/taglib/taglib/mpeg/id3v2/)
include_directories(../3dparty/taglib/taglib/mpeg/id3v2/frames/)

include_directories(../3dparty/taglib/taglib/frames/)
include_directories(../3dparty/taglib/taglib/toolkit/)
include_directories(../build/3dparty/taglib/)


set(SOURCES main.cpp src/mainwindow.cpp src/fileInfo.cpp)
set(HEADERS src/mainwindow.h)
set(UI src/mainwindow.ui)

add_executable(utag ${SOURCES} ${HEADERS} ${UI})

add_subdirectory(src)
include_directories(./src)

target_link_libraries(utag tag Qt5::Core Qt5::Widgets)

#add_compile_options(
#    -std=c++17
#)
