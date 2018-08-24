if (GETTEXT_XGETTEXT_EXECUTABLE)
  # Already in cache, be silent
  set (XGETTEXT_FIND_QUIETLY TRUE)
endif (GETTEXT_XGETTEXT_EXECUTABLE)

find_program(GETTEXT_XGETTEXT_EXECUTABLE xgettext)
if (GETTEXT_XGETTEXT_EXECUTABLE)
  set(XGETTEXT_FOUND TRUE)
  if (NOT XGETTEXT_FIND_QUIETLY)
    message(STATUS "Found xgettext: ${GETTEXT_XGETTEXT_EXECUTABLE}")
  endif (NOT XGETTEXT_FIND_QUIETLY)
else (GETTEXT_XGETTEXT_EXECUTABLE)
  set(XGETTEXT_FOUND FALSE)
  if (XGettext_REQUIRED)
    message(STATUS "xgettext not found")
  endif (XGettext_REQUIRED)
endif (GETTEXT_XGETTEXT_EXECUTABLE)


if(GETTEXT_XGETTEXT_EXECUTABLE)
  execute_process(
    COMMAND
      "${GETTEXT_XGETTEXT_EXECUTABLE}" "--version"
    OUTPUT_VARIABLE
      xgettext_version
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(xgettext_version MATCHES "^xgettext \\(.*\\) [0-9]")
    string(REGEX REPLACE "^xgettext \\([^\\)]*\\) ([0-9\\.]+[^ \n]*).*" "\\1" GETTEXT_XGETTEXT_VERSION_STRING "${xgettext_version}")
  endif()
  unset(xgettext_version)
endif()
