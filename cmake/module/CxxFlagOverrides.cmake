# [Make Override Files](https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#make-override-files)

if (MSVC)
    # remove default warning level from CMAKE_CXX_FLAGS_INIT
    string (REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
endif()
