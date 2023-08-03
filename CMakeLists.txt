cmake_minimum_required(VERSION 3.22)

project(twinNavigator)

add_definitions("-Werror=return-type")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Svg REQUIRED)
qt5_add_resources(QRC_SOURCES res/icons.qrc)

set(EDITOR_SOURCES editor/editorwindow.cpp)

set(PROJECT_SOURCES main.cpp FilePanel.h PanelWidget.h MarkableItem.h
        MainWindow.cpp
        MainWindow.h
        PanelWidget.cpp
        Config.cpp
        Config.h
        ${EDITOR_SOURCES}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${QRC_SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Svg)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
