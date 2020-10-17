set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fileInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/errordialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FileTable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TableView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CommandEdit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Preferences.cpp
)
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fileInfo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/errordialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FileTable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TableView.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CommandEdit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Preferences.h
)
set(UI
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Preferences.ui
)

add_library(src_lib STATIC ${SOURCES} ${HEADERS} ${UI})

target_link_libraries(src_lib Qt5::Core Qt5::Widgets)
