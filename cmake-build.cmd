@echo off
setlocal

rem [What is the current directory in a batch file?](
rem  https://stackoverflow.com/questions/4419868/what-is-the-current-directory-in-a-batch-file)
set SCRIPT_PATH=%~dp0
set MY_SOURCE_DIR=%SCRIPT_PATH%
rem set MY_BUILD_DIR=%cd%
set MY_BUILD_DIR=%MY_SOURCE_DIR%\build

set CMAKE_CXX_COMPILER=Clang
set CMAKE_GENERATOR="Ninja"

set BOOST_ROOT="D:\My\IBIS\boost_1_76_0"
set Boost_COMPILER="-clangw11"

rem Debug, Release, RelWithDebInfo, MinSizeRel
set CMAKE_BUILD_TYPE=Release

echo ##
echo ## Configure:
echo ##
echo ## Source directory: %MY_SOURCE_DIR%
echo ## Build directoy:   %MY_BUILD_DIR%
echo ## Build type:       %CMAKE_BUILD_TYPE%
echo ## Build generator:  %CMAKE_GENERATOR%
echo ## Compiler:         %CMAKE_CXX_COMPILER%

cmake -E make_directory %MY_BUILD_DIR%

cd %MY_BUILD_DIR%

rem Load MSVC console build environment
rem call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
call  "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsx86_amd64.bat"

cmake -S%MY_SOURCE_DIR% -B%MY_BUILD_DIR% ^
    -G %CMAKE_GENERATOR% ^
    -DBOOST_ROOT=%BOOST_ROOT% ^
    -DBoost_USE_STATIC_LIBS=TRUE ^
    -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% ^
    -DCMAKE_CXX_COMPILER=%CMAKE_CXX_COMPILER% ^
    -DBoost_COMPILER=%Boost_COMPILER% ^
    -DCMAKE_INSTALL_PREFIX=stage ^
    -DBUILD_SHARED_LIBS:BOOL=OFF ^
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

rem cleanup before the run cmake
cmake --build %MY_BUILD_DIR% --target clean

rem make && build
rem cmake --build %MY_BUILD_DIR% --target all --config %CMAKE_BUILD_TYPE%

rem wait for user
rem set /p temp="Hit enter to continue"
