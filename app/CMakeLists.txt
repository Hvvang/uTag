cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(TAGLIB_PATH "../3dparty/taglib/taglib")

find_library(TAGLIB taglib)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(
        ./src
        ${TAGLIB_PATH}/ape
        ${TAGLIB_PATH}/asf
        ${TAGLIB_PATH}/flac
        ${TAGLIB_PATH}/it
        ${TAGLIB_PATH}/mod
        ${TAGLIB_PATH}/mp4
        ${TAGLIB_PATH}/mpc
        ${TAGLIB_PATH}/mpeg
        ${TAGLIB_PATH}/mpeg/id3v2
        ${TAGLIB_PATH}/mpeg/id3v2/frames
        ${TAGLIB_PATH}/ogg
        ${TAGLIB_PATH}/riff
        ${TAGLIB_PATH}/s3m
        ${TAGLIB_PATH}/toolkit
        ${TAGLIB_PATH}/trueaudio
        ${TAGLIB_PATH}/wavpack
        ${TAGLIB_PATH}/xm
        ${TAGLIB_PATH}
)

add_compile_options(
-Wall
-Wextra
-Werror
-Wpedantic
)

add_subdirectory(src)
add_executable(utag main.cpp)
target_link_libraries(utag tag src_lib Qt5::Core Qt5::Widgets)
