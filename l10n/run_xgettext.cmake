################################################################################
## l10n/run_xgettext.cmake
################################################################################

##
# assemble a text file from given variables cmake script to be used directly
# by xggettext
include("${SOURCES}") 
 
foreach(MY_TARGET ${MY_TARGETS})
    foreach(SOURCE ${${MY_TARGET}_SOURCES}) 
        list(APPEND SOURCES_WITH_ABSOLUTE_PATHS ${${MY_TARGET}_SOURCE_DIR}/${SOURCE})
    endforeach()
endforeach()

# due to generator expressions in the target_sources() used the list contains 
# empty elements which must be removed before written out to the file used
# by xgettext 
list(JOIN SOURCES_WITH_ABSOLUTE_PATHS "\n" SOURCES_WITH_ABSOLUTE_PATHS_NL)

file(WRITE ${CMAKE_BINARY_DIR}/sources.txt
    "${SOURCES_WITH_ABSOLUTE_PATHS_NL}"
)


message(STATUS "generating l10n file ${POT_FILE}")

# config area
set(l10n_email "https://github.com/eda/ibis/issues")


# [Extracting messages from the source code](
#  https://www.boost.org/doc/libs/1_67_0/libs/locale/doc/html/messages_formatting.html#extracting_messages_from_code)
# Note: running in -P script mode, CMake sets the variables CMAKE_BINARY_DIR etc.
# to the current working directory (https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html).
execute_process(
    COMMAND xgettext
        --add-comments=TRANSLATORS
        --msgid-bugs-address=${l10n_email}    
        --from-code=UTF-8
        --keyword=translate:1,1t 
        --keyword=translate:1c,2,2t
        --keyword=translate:1,2,3t
        --keyword=translate:1c,2,3,4t
        --keyword=gettext:1 
        --keyword=pgettext:1c,2
        --keyword=ngettext:1,2
        --keyword=npgettext:1c,2,3
        --no-wrap
        --files-from=${CMAKE_BINARY_DIR}/sources.txt
        --output=${POT_FILE}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}      
)

