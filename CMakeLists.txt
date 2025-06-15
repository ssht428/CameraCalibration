cmake_minimum_required(VERSION 3.5)

project(CameraCalibration VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Xml)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Xml)

set(THIRDPARTY_INCLUDE_DIR "thirdparty")
aux_source_directory("thirdparty/libcbdetect" LIBCBDETECT_SOURCE_LIST)
aux_source_directory("thirdparty/libDockingPanes" LIBDOCKINGPANES_SOURCE_LIST)



set(OpenCV_DIR "D:/Learn/OpenCV411/opencv/build")
find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
    ${THIRDPARTY_INCLUDE_DIR}
)

set(PROJECT_SOURCES
        ${LIBCBDETECT_SOURCE_LIST}
        ${LIBDOCKINGPANES_SOURCE_LIST}
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        setting.cpp
        setting.h
        setting.ui
        pic.qrc
        thirdparty/libDockingPanes/resources/images.qrc
)


add_executable(CameraCalibration
    ${PROJECT_SOURCES}
)


target_link_libraries(CameraCalibration PRIVATE 
Qt5::Widgets 
Qt5::Core
Qt5::Xml
${OpenCV_LIBS}
)

set_target_properties(CameraCalibration PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CameraCalibration
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

