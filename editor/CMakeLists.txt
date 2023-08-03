find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(editorLibName builtin-editor)
file(GLOB SOURCES *.cpp)

add_library(${editorLibName} STATIC ${SOURCES})

target_include_directories(${editorLibName} PRIVATE ${Qt5Widgets_INCLUDE_DIRS})

target_link_libraries(${editorLibName} PRIVATE Qt5::Widgets)

