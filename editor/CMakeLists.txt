find_package(Qt5 COMPONENTS Widgets Svg REQUIRED)

set(KF_DIR_SYNTAX "/usr/include/KF5/KSyntaxHighlighting")
set(KF_LIB_SYNTAX KF5SyntaxHighlighting)

IF(NOT EXISTS ${KF_DIR_SYNTAX})
    message(FATAL_ERROR "Not found ${KF_DIR_SYNTAX} major version = 5")
ELSE()
    message(STATUS "Found ${KF_DIR_SYNTAX} major version = 5")
    IF(NOT EXISTS "${KF_DIR_SYNTAX}/repository.h")
        set(KF_DIR_SYNTAX "${KF_DIR_SYNTAX}/KSyntaxHighlighting") #Manjaro
    ENDIF()
ENDIF()

set(BOTAN_DIR "/usr/include/botan-2")
IF(NOT EXISTS ${BOTAN_DIR})
    message(FATAL_ERROR "Not found ${BOTAN_DIR}")
ELSE()
    message(STATUS "Found ${BOTAN_DIR}")
ENDIF()

set(editorLibName builtin-editor)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt5_add_resources(QRC_SOURCES1 res/icons1.qrc)

file(GLOB SOURCES *.cpp)
add_library(${editorLibName} STATIC ${SOURCES} ${QRC_SOURCES1})
target_include_directories(${editorLibName} PRIVATE ${Qt5Widgets_INCLUDE_DIRS}
        ${KF_DIR_SYNTAX} ${BOTAN_DIR})
target_link_libraries(${editorLibName} PRIVATE Qt5::Widgets Qt5::Svg ${KF_LIB_SYNTAX} X11 botan-2)

