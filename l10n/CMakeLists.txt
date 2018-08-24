################################################################################
## l10n/CMakeLists.txt
################################################################################

project(eda_l10n)


set(language_template ${PROJECT_SOURCE_DIR}/eda.pot)

find_package(Gettext)
find_package(XGettext)


##
# XGetText
# thanks to ngladitz fron cmake IIRC channel for the help here
if (XGETTEXT_FOUND)
message(STATUS "Found XGetText package")

# create a cmake variables script where the sources and directories of the
# sub projects are  set ...
set(SUBPROJECT_LIST "eda_common;eda_vhdl_parser;ibis")
set(MY_CONTENT "set(MY_TARGETS \"${SUBPROJECT_LIST}\")\n")
foreach(project ${SUBPROJECT_LIST})
    string(APPEND MY_CONTENT
        "set(${project}_SOURCES    \"$<TARGET_PROPERTY:${project},SOURCES>\")\n"
        "set(${project}_SOURCE_DIR \"$<TARGET_PROPERTY:${project},SOURCE_DIR>\")\n"
    )
endforeach()

# ... and write the contents to a file at generation time
file(GENERATE OUTPUT ${PROJECT_BINARY_DIR}/sources.cmake
    CONTENT "${MY_CONTENT}"
)


# ... finaly invoke the run_xgettext cmake script with the path to the 
# variables script and template PO file using cmake's '-P' parameter at build
# time.
add_custom_target(extract-translations 
    COMMAND ${CMAKE_COMMAND} 
        -DSOURCES=${PROJECT_BINARY_DIR}/sources.cmake 
        -DPOT_FILE=${language_template}
        -P ${PROJECT_SOURCE_DIR}/run_xgettext.cmake
# sed not on windows        
#    COMMAND sed -i
#        's/charset=CHARSET/charset=UTF-8/'
#        ${language_template}                     
    DEPENDS ${PROJECT_BINARY_DIR}/sources.cmake 
    COMMENT "Extract translatable messages from source"
)


add_custom_target(l10n ALL
    DEPENDS extract-translations 
)

endif(XGETTEXT_FOUND)


##
# GetText
if (GETTEXT_FOUND)
message(STATUS "Found GetText package")

file(GLOB translations_po ${PROJECT_SOURCE_DIR}/po/*.po)
GETTEXT_CREATE_TRANSLATIONS(${language_template} ALL ${translations_po})

endif(GETTEXT_FOUND)
