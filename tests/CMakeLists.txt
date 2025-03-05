find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test QuickTest)
find_program(GLIB_COMPILE_SCHEMAS glib-compile-schemas REQUIRED)


###
### schema
###

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gschemas.compiled
    COMMAND ${GLIB_COMPILE_SCHEMAS} ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/com.ubports.gsettings.test.gschema.xml
    COMMENT "Compiling GSettings schemas"
)

add_custom_target(schema ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/gschemas.compiled
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/com.ubports.gsettings.test.gschema.xml
    ${CMAKE_CURRENT_BINARY_DIR}/com.ubports.gsettings.test.gschema.xml
    COPYONLY
)

###
### cpptest
###

add_executable(cpptest
    cpptest.cpp
)

target_include_directories(cpptest PRIVATE
    ${CMAKE_SOURCE_DIR}/../src
)

target_link_libraries(cpptest PRIVATE
    Qt::Test
    Qt::Core
    gsettings-qt
    PkgConfig::Glib2
)

add_test(NAME cpptest COMMAND cpptest)

add_dependencies(cpptest schema)

set_tests_properties(cpptest PROPERTIES
    ENVIRONMENT "GSETTINGS_SCHEMA_DIR=${CMAKE_CURRENT_BINARY_DIR};GSETTINGS_BACKEND=memory"
)


###
### qmltest
###

add_executable(qmltest
    test.cpp
)

target_include_directories(qmltest PRIVATE
    ${CMAKE_SOURCE_DIR}/../src
)

target_link_libraries(qmltest PRIVATE
    Qt::Test
    Qt::Core
    Qt::QuickTest
    gsettings-qt
    PkgConfig::Glib2
)

add_test(NAME qmltest COMMAND qmltest)

add_dependencies(qmltest schema)

set_tests_properties(qmltest PROPERTIES
    ENVIRONMENT "GSETTINGS_SCHEMA_DIR=${CMAKE_CURRENT_BINARY_DIR};GSETTINGS_BACKEND=memory;QT_QPA_PLATFORM=minimal;QML2_IMPORT_PATH=${CMAKE_BINARY_DIR}"
)

add_custom_command(
    TARGET qmltest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/tst_GSettings.qml ${CMAKE_CURRENT_BINARY_DIR}/tst_GSettings.qml
)
