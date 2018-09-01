@echo off
setlocal

rem https://crascit.com/2016/04/03/scripting-cmake-builds/
rem https://cmake.org/cmake/help/v3.12/manual/cmake.1.html#command-line-tool-mode

rem [How to get the path of the batch script in Windows?](
rem  https://stackoverflow.com/questions/3827567/how-to-get-the-path-of-the-batch-script-in-windows?answertab=active#tab-top)
set SCRIPT_PATH=%~dp0
set EDA_SOURCE_DIR=%SCRIPT_PATH%
set EDA_BUILD_DIR=%EDA_SOURCE_DIR%..\build

set CMAKE_GENERATOR="Eclipse CDT4 - Ninja"

rem Debug, Release, RelWithDebInfo, MinSizeRel
set CMAKE_BUILD_TYPE=Release


echo ##
echo ## Configure from Source %EDA_SOURCE_DIR%
echo ## Build in %EDA_BUILD_DIR%
echo ## %CMAKE_BUILD_TYPE%
echo ##

cmake -E make_directory %EDA_BUILD_DIR%

cd %EDA_BUILD_DIR%

cmake %EDA_SOURCE_DIR% ^
    -G %CMAKE_GENERATOR% ^
    -DCMAKE_ECLIPSE_VERSION=4.6 ^
    -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE ^
    -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% ^
    -DCMAKE_RULE_MESSAGES:BOOL=ON ^
    -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ^
    -DCMAKE_INSTALL_PREFIX=stage ^
    -DBUILD_SHARED_LIBS:BOOL=OFF ^
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        
cmake --build %EDA_BUILD_DIR% --target all --config %CMAKE_BUILD_TYPE%

rem set /p temp="Hit enter to continue"
