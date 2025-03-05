cmake_minimum_required(VERSION 3.18)
project(gsettings-qt VERSION 1.0.0 LANGUAGES CXX)

option(ENABLE_WERROR "Enable -Werror" OFF)
option(ENABLE_QT6 "Enable Qt6 build" OFF)

add_compile_options(-Wall -Wextra -pedantic)
if (WERROR)
    add_compile_options(-Werror)
endif()

if (ENABLE_QT6)
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Qml)
    set (QT_VERSION_IN_LIBNAME ${QT_VERSION_MAJOR})
else()
    find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Qml)
    set(QT_VERSION_IN_LIBNAME "")
endif()

set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)

set(QGSETTINGS_SO_VERSION_MAJOR "1")
set(QGSETTINGS_SO_VERSION_MINOR "0")
set(QGSETTINGS_SO_VERSION_MICRO "0")
set(QGSETTINGS_SO_VERSION ${QGSETTINGS_SO_VERSION_MAJOR})

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Qml)
find_package(PkgConfig REQUIRED)
pkg_check_modules(Gio REQUIRED IMPORTED_TARGET gio-2.0)

enable_testing()

if(BUILD_TESTING)
    pkg_check_modules(Glib2 REQUIRED IMPORTED_TARGET glib-2.0)
endif()

add_subdirectory(src)
add_subdirectory(GSettings)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
