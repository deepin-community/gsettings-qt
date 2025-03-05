# qt signal slot syntax, use Q_SIGNALS, Q_SLOTS, and Q_EMIT
add_definitions(-DQT_NO_KEYWORDS)

set(QT_INCLUDE_DIR      ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LIBRARY_ARCHITECTURE}/qt${QT_VERSION_MAJOR})
set(QT_FULL_INCLUDE_DIR ${CMAKE_INSTALL_FULL_INCLUDEDIR}/${CMAKE_LIBRARY_ARCHITECTURE}/qt${QT_VERSION_MAJOR})

add_library(gsettings-qt${QT_VERSION_IN_LIBNAME} SHARED
    qgsettings.cpp
    util.cpp
    qconftypes.cpp
    qgsettings.h
    util.h
    qconftypes.h
)

set_target_properties(gsettings-qt${QT_VERSION_IN_LIBNAME} PROPERTIES
    SOVERSION ${QGSETTINGS_SO_VERSION}
    VERSION ${QGSETTINGS_SO_VERSION_MAJOR}.${QGSETTINGS_SO_VERSION_MINOR}.${QGSETTINGS_SO_VERSION_MICRO}
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(gsettings-qt${QT_VERSION_IN_LIBNAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/QGSettings>
)

target_link_libraries(gsettings-qt${QT_VERSION_IN_LIBNAME}
    PUBLIC
        Qt::Core
    PRIVATE
        PkgConfig::Gio
)

install(TARGETS gsettings-qt${QT_VERSION_IN_LIBNAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
)

install(FILES qgsettings.h
              QGSettings
        DESTINATION ${QT_FULL_INCLUDE_DIR}/QGSettings
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/gsettings-qt.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/gsettings-qt${QT_VERSION_IN_LIBNAME}.pc
    @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gsettings-qt${QT_VERSION_IN_LIBNAME}.pc
        DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig
)
