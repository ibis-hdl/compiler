@echo off
setlocal

rem [How to get the path of the batch script in Windows?](
rem  https://stackoverflow.com/questions/3827567/how-to-get-the-path-of-the-batch-script-in-windows?answertab=active#tab-top)
set SOURCE_PATH=%~dp0
set WORK_PATH=%cd%

rem Debug, Release, RelWithDebInfo, MinSizeRel
set BUILD_TYPE=Release


echo ##
echo ## Configure Build in %WORK_PATH%
echo ##

cmake %SOURCE_PATH% ^ 
    -G "Eclipse CDT4 - MinGW Makefiles" ^
    -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE ^
    -DCMAKE_ECLIPSE_VERSION=4.6 ^
    -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j4 ^
    -DCMAKE_MAKE_PROGRAM=mingw32-make ^
    -DCMAKE_RULE_MESSAGES:BOOL=OFF ^
    -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    -DCMAKE_INSTALL_PREFIX=stage ^
    -DBUILD_SHARED_LIBS:BOOL=OFF ^
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        

rem set /p temp="Hit enter to continue"
