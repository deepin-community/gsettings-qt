find_package(QmlPlugins)

set(CHECK_DEFAULT_PATH "")
if (EXISTS "/etc/debian_version")
    set(CHECK_DEFAULT_PATH "NO_DEFAULT_PATH")
endif()
find_program(QML_PLUGIN_DUMP qmlplugindump REQUIRED
                 PATHS /usr/lib/qt${QT_VERSION_MAJOR}/bin
                 ${CHECK_DEFAULT_PATH}
)

add_definitions(-DQT_NO_KEYWORDS)

set(URI "GSettings")
set(API_VER "1.0")
set(QML_PLUGIN_DIR "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml/${URI}")

add_library(GSettingsQmlPlugin MODULE
    plugin.cpp
    gsettings-qml.cpp
    plugin.h
    gsettings-qml.h
)
target_include_directories(GSettingsQmlPlugin PRIVATE
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(GSettingsQmlPlugin PRIVATE
    Qt::Core
    Qt::Qml
    gsettings-qt${QT_VERSION_IN_LIBNAME}
    PkgConfig::Gio
)

add_qmlplugin(${URI}
              ${API_VER}
              ${URI}
              TARGET_PREFIX ${URI}
              TARGETS GSettingsQmlPlugin
)

if(NOT CMAKE_CROSSCOMPILING)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/plugins.qmltypes
        COMMAND ${QML_PLUGIN_DUMP} -noinstantiate -notrelocatable ${URI} ${API_VER} ../ > ${CMAKE_CURRENT_BINARY_DIR}/plugins.qmltypes
        DEPENDS GSettingsQmlPlugin
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )

    add_custom_target(GSettings_generated_files ALL SOURCES ${CMAKE_CURRENT_BINARY_DIR}/plugins.qmltypes)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/plugins.qmltypes DESTINATION ${QML_PLUGIN_DIR})
endif()
