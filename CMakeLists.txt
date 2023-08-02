cmake_minimum_required(VERSION 3.13)

project(twinNavigator)

add_definitions("-Werror=return-type")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES main.cpp FilePanel.h PanelWidget.h MarkableItem.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
            res/icons.qrc
        ${PROJECT_SOURCES}
    )
else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()