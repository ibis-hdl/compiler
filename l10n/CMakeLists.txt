################################################################################
## l10n/CMakeLists.txt
################################################################################

project(eda_l10n)


find_package(Gettext)
find_package(XGettext)


##
# XGetText
# thanks to ngladitz fron cmake IIRC channel for the help here
if (XGETTEXT_FOUND)
message(STATUS "Found XGetText packge")

# create a cmake variables script where the sources and directories of the
# sub projects are  set ...
set(SUBPROJECT_LIST "eda_common;eda_vhdl_parser;ibis")
set(MY_CONTENT "")
foreach(project ${SUBPROJECT_LIST})
    string(APPEND MY_CONTENT
        "set(${project}_SOURCES    \"$<TARGET_PROPERTY:${project},SOURCES>\")\n"
        "set(${project}_SOURCE_DIR \"$<TARGET_PROPERTY:${project},SOURCE_DIR>\")\n"
    )
endforeach()
string(APPEND MY_CONTENT "set(MY_TARGETS \"${SUBPROJECT_LIST}\")\n")

# ... and write the contents to file
file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/l10n/sources.cmake
    CONTENT "${MY_CONTENT}"
)


# ... finaly invoke the xgettext script with the path to variables script and
# template PO file with '-P'
set(pot_file ${CMAKE_SOURCE_DIR}/l10n/eda.pot)

add_custom_target(extract-translations 
    COMMAND ${CMAKE_COMMAND} 
        -DSOURCES=${CMAKE_BINARY_DIR}/l10n/sources.cmake 
        -DPOT_FILE=${pot_file}
        -P ${CMAKE_SOURCE_DIR}/l10n/run_xgettext.cmake
    COMMAND sed -i
        's/charset=CHARSET/charset=UTF-8/'
        ${pot_file}                     
    COMMENT "Extract translatable messages to ${pot_file}"
)


add_custom_target(l10n ALL
    DEPENDS ${pot_file}
)

endif(XGETTEXT_FOUND)


##
# GetText
if (GETTEXT_FOUND)
message(STATUS "Found GetText packge")

file(GLOB pofiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.po)
GETTEXT_CREATE_TRANSLATIONS(${GETTEXT_PACKAGE}.pot ALL ${pofiles})

endif(GETTEXT_FOUND)


# https://github.com/flplv/vala-cmake-example/blob/master/po/CMakeLists.txt
# https://github.com/GenisysPro/CenisysPro/blob/master/po/CMakeLists.txt
# https://github.com/eiskaltdcpp/eiskaltdcpp/blob/master/cmake/CMakeLists.txt
# https://github.com/jarro2783/CMake-Gettext/blob/master/GettextTranslate.cmake
# 
