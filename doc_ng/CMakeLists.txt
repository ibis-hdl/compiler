################################################################################
## EDA/doc project
##
## file: doc_ng/CMakeLists.txt
################################################################################

## API documentation with Sphinx and Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION_NG "Create and install the HTML based API documentation (requires Doxygen & Sphinx)" ${DOXYGEN_FOUND})


# Note, ensurepip module requires Python >= 3.4
find_package(Python3 3.6 COMPONENTS Interpreter REQUIRED)


##
# target helper to setup Sphinx-doc
#
# Using Python's [Virtual Environments and Packages](https://docs.python.org/3/tutorial/venv.html)
# and [Activating a virtual environment](https://pythonise.com/categories/python/python-virtual-environments-with-the-venv-command#activating-a-virtual-environment)
# self-bootstrap pip, see [Installation](https://pip.pypa.io/en/stable/installing/),
# and install requirements.
# Python's virtual environment used to avoid pollution of user's Python directory.
#
# FixMe: Activating/Deactivating Python's virtual environments differs completely
# on Windows and Linux/Unix :(
set(_py_vENV "${CMAKE_CURRENT_BINARY_DIR}/py_venv")

add_custom_command(OUTPUT "${_py_vENV}"
    COMMENT "Setup Python's virtual environment to generate documentation."
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/py_requirements.txt
    # command batch
    COMMAND ${Python3_EXECUTABLE} -m venv ${_py_vENV}
    #COMMAND ${_py_vENV}/Scripts/activate
    COMMAND source ${_py_vENV}/bin/activate
    COMMAND python -m ensurepip
    COMMAND python -m pip install --upgrade pip
    COMMAND pip install wheel --upgrade
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/py_requirements.txt requirements.txt
    COMMAND pip install --no-cache-dir -r requirements.txt --upgrade
    #COMMAND ${_py_vENV}/Scripts/deactivate
    COMMAND deactivate
    VERBATIM
)

# prevent cleaning up, see
# https://cmake.org/cmake/help/latest/prop_dir/CLEAN_NO_CUSTOM.html
#
# FixMe: Ninja did a design decision to not clean non empty directories
# e.g. [Silently ignore non-empty directories during 'clean' #1334](
# https://github.com/ninja-build/ninja/pull/1334), approch mention at
# [Looking for a 'cmake clean' command to clear up CMake output](
# https://stackoverflow.com/questions/9680420/looking-for-a-cmake-clean-command-to-clear-up-cmake-output)
# may help here.
# FixMe: make venv non cleanable ...
if(EXISTS "${_py_vENV}" AND IS_DIRECTORY "${_py_vENV}")
    #set_property(DIRECTORY "${_py_vENV}"
    #    PROPERTY CLEAN_NO_CUSTOM TRUE
    #)
endif()


##
# target helper for running Sphinx-doc
#
# determine relative path to conf.py which is a variable inside conf.py
set(_doxygen_output_dir "${CMAKE_CURRENT_BINARY_DIR}/doxy_output")
file(RELATIVE_PATH _doxygen_output_rel_dir
    # strange, but works. I would expect ${CMAKE_CURRENT_SOURCE_DIR} ...
    "${CMAKE_CURRENT_SOURCE_DIR}/source/conf.py" "${_doxygen_output_dir}"
)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
    ${CMAKE_CURRENT_BINARY_DIR}/source/conf.py
    @ONLY
)
#message(STATUS "doxygen's relative output path: ${_doxygen_output_rel_dir}")

# copy resources to build directory since Sphinx works with relative paths to conf.py
file(COPY index.rst _static _templates
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/source"
)

# call sphinx-build inside Python's virtual environment to generate the docs
# Note, doxygen doesn't create the path for 'WARN_LOGFILE'.
add_custom_command(OUTPUT build
    COMMENT "Generating API documentation using Sphinx + Exhale + Breathe + Doxygen"
    DEPENDS
        ${_py_vENV}
        ${CMAKE_CURRENT_BINARY_DIR}/source/conf.py
        ${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
    # command batch
    COMMAND ${CMAKE_COMMAND} -E make_directory "${_doxygen_output_dir}"
    #COMMAND ${_py_vENV}/Scripts/activate
    COMMAND source ${_py_vENV}/bin/activate
    COMMAND sphinx-build -M html ./source ./build
    #COMMAND ${_py_vENV}/Scripts/deactivate
    COMMAND deactivate
    VERBATIM
)


##
# the doc target self
add_custom_target(doc-ng
    DEPENDS "${_py_vENV}" "build"
)


if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(WARNING "=> Configure Fix: Doxygen is needed to build the documentation, disabled")
        set(BUILD_DOCUMENTATION OFF CACHE BOOL "doxygen (not found)" FORCE)
    endif()
    if(NOT Python3_Interpreter_FOUND)
        # paranoia ;-)
        message(WARNING "=> Configure Fix: Python3 is needed to build the documentation, disabled")
        set(BUILD_DOCUMENTATION OFF CACHE BOOL "python3 (not found)" FORCE)
    endif()
endif()
