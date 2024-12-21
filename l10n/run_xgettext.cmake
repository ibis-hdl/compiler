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

# [list(REMOVE_ITEM) not working in cmake](
#  https://stackoverflow.com/questions/36134129/listremove-item-not-working-in-cmake)
#
# Filter values through regex
#   filter_regex({INCLUDE | EXCLUDE} <regex> <listname> [items...])
#   Element will included into result list if
#     INCLUDE is specified and it matches with regex or
#     EXCLUDE is specified and it doesn't match with regex.
# Example:
#   filter_regex(INCLUDE "(a|c)" LISTOUT a b c d) => a c
#   filter_regex(EXCLUDE "(a|c)" LISTOUT a b c d) => b d
function(filter_regex _action _regex _listname)
    # check an action
    if("${_action}" STREQUAL "INCLUDE")
        set(has_include TRUE)
    elseif("${_action}" STREQUAL "EXCLUDE")
        set(has_include FALSE)
    else()
        message(FATAL_ERROR "Incorrect value for ACTION: ${_action}")
    endif()

    set(${_listname})
    foreach(element ${ARGN})
        string(REGEX MATCH ${_regex} result ${element})
        if(result)
            if(has_include)
                list(APPEND ${_listname} ${element})
            endif()
        else()
            if(NOT has_include)
                list(APPEND ${_listname} ${element})
            endif()
        endif()
    endforeach()

    # put result in parent scope variable
    set(${_listname} ${${_listname}} PARENT_SCOPE)
endfunction()

# remove PCH headers
filter_regex(EXCLUDE ".*ibis_pch\\.hxx(\\.cxx)?"
    SOURCES_WITH_ABSOLUTE_PATHS ${SOURCES_WITH_ABSOLUTE_PATHS}
)

# due to generator expressions in the target_sources() used the list contains
# empty elements which must be removed before written out to the file used
# by xgettext
list(JOIN SOURCES_WITH_ABSOLUTE_PATHS "\n" SOURCES_WITH_ABSOLUTE_PATHS_NL)

file(WRITE ${PROJECT_BINARY_DIR}/sources.txt
    "${SOURCES_WITH_ABSOLUTE_PATHS_NL}"
)


message(STATUS "generating l10n file ${POT_FILE} using ${GETTEXT_XGETTEXT_EXECUTABLE}")

# config area
set(l10n_email "https://github.com/eda/ibis/issues")


# [Extracting messages from the source code](
#  https://www.boost.org/doc/libs/1_67_0/libs/locale/doc/html/messages_formatting.html#extracting_messages_from_code)
# Note: running in -P script mode, CMake sets the variables CMAKE_BINARY_DIR etc.
# to the current working directory (https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html).
execute_process(
    COMMAND xgettext # XXXX ${GETTEXT_XGETTEXT_EXECUTABLE}
        --add-comments=TRANSLATORS
        --package-name="${PROJECT_NAME}"
        --package-version="${eda_VERSION_MAJOR}.${eda_VERSION_MINOR}.${eda_VERSION_REVISION}"
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

