cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(ezcom VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(LibEZTP 1.1.0 REQUIRED)

if(ANDROID)
  add_library(ezcom SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(ezcom
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ezmaker/dialog.cpp
    ezmaker/dialog.h
    ezmaker/dialog.ui
  )
endif()

target_link_libraries(ezcom PRIVATE Qt5::Widgets)
target_link_libraries(ezcom PRIVATE LibEZTP::LibEZTP)
