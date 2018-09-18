# [How to set compiler options with CMake in Visual Studio 2017](
# https://stackoverflow.com/questions/45995784/how-to-set-compiler-options-with-cmake-in-visual-studio-2017)

# log all *_INIT variables
function(log_ini_vars)
    message(STATUS "---------- CMAKE default settings ----------")
    get_cmake_property(_varNames VARIABLES)
    list (REMOVE_DUPLICATES _varNames)
    list (SORT _varNames)
    foreach (_varName ${_varNames})
        if (_varName MATCHES "_INIT$")
            message(STATUS "${_varName}=${${_varName}}")
        endif()
    endforeach()
    message(STATUS "------------------- end --------------------")
endfunction()


if (MSVC)
    # remove default warning level from CMAKE_CXX_FLAGS_INIT
    string (REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
endif()


#log_ini_vars()
