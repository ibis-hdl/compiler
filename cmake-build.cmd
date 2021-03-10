@echo off
setlocal

rem [What is the current directory in a batch file?](
rem  https://stackoverflow.com/questions/4419868/what-is-the-current-directory-in-a-batch-file)
set SCRIPT_PATH=%~dp0
set EDA_SOURCE_DIR=%SCRIPT_PATH%
set EDA_BUILD_DIR=%cd%

set CMAKE_BUILD_TOOL=Ninja
set CMAKE_CXX_COMPILER=clang++
set CMAKE_GENERATOR="${CMAKE_BUILD_TOOL}"

rem Debug, Release, RelWithDebInfo, MinSizeRel
set CMAKE_BUILD_TYPE=RelWithDebInfo


echo ##
echo ## Configure:
echo ##

echo ## Source directory: %EDA_SOURCE_DIR%
echo ## Build directoy:   %EDA_BUILD_DIR%
echo ## Build type:       %CMAKE_BUILD_TYPE%
echo ## Build tool:       %CMAKE_BUILD_TOOL%
echo ## Compiler:         %CMAKE_CXX_COMPILER%

cmake -E make_directory %EDA_BUILD_DIR%

cd %EDA_BUILD_DIR%

cmake %EDA_SOURCE_DIR% ^
    -G %CMAKE_GENERATOR% ^
    -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% ^
    -DCMAKE_RULE_MESSAGES:BOOL=ON ^
    -DCMAKE_CXX_COMPILER=%CMAKE_CXX_COMPILER%  ^
    -DCMAKE_INSTALL_PREFIX=stage ^
    -DBUILD_SHARED_LIBS:BOOL=OFF ^
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# cleanup before the run cmake
cmake --build %EDA_BUILD_DIR% --target clean

# make && build
cmake --build %EDA_BUILD_DIR% --target all --config %CMAKE_BUILD_TYPE%

# wait for user
set /p temp="Hit enter to continue"
