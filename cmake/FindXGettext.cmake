message(STATUS "XGetText")


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


# see https://github.com/Valama/valama/blob/master/cmake/Gettext.cmake
# for how to get version informations
