## -----------------------------------------------------------------------------
## virtual python environment configuration
## -----------------------------------------------------------------------------

find_package(Python3 COMPONENTS Interpreter REQUIRED)

##
# target helper to setup Python's virtual environment
#
# Python's virtual environment is used to avoid pollution of user's Python directory.
#
# FixMe: Find a way to exclude the 'command' venv from clean target. Using ${PY_ENV}
# as dependency results on an ninja error:  remove(doc/venv): Permission denied
# Using a 'tag' file approach as dependency calls each time the 'command' to recreate
# the venv.
#
# See: using Python's [Virtual Environments and Packages](https://docs.python.org/3/tutorial/venv.html)
# and [Activating a virtual environment](https://pythonise.com/categories/python/python-virtual-environments-with-the-venv-command#activating-a-virtual-environment)
# self-bootstrap pip, see [Installation](https://pip.pypa.io/en/stable/installing/),
# and install requirements.
set(PY_ENV ${CMAKE_BINARY_DIR}/venv)

# create virtual environment
add_custom_command(OUTPUT ${PY_ENV}
    COMMENT "Create and initialize Python's virtual environment."
    DEPENDS
        ${CMAKE_SOURCE_DIR}/cmake/py_requirements.txt
    # command batch
    COMMAND ${Python3_EXECUTABLE} -m venv ${PY_ENV}
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/activate,source;${PY_ENV}/bin/activate>"
    COMMAND python -m ensurepip
    COMMAND python -m pip install --upgrade pip
    COMMAND pip install wheel --upgrade
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/cmake/py_requirements.txt requirements.txt
    COMMAND pip install --no-cache-dir -r requirements.txt --upgrade
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/deactivate,deactivate>"
    COMMAND_EXPAND_LISTS
)

# the target for Python's virtual environment
add_custom_target(ibis-pyenv
    COMMENT "Setup Python's virtual environment."
    DEPENDS ${PY_ENV}
)
