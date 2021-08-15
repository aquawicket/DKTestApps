@ECHO off

set "DIGITALKNOB=C:\Users\%USERNAME%\digitalknob"
set "DK=%DIGITALKNOB%\DK"
set "DKTESTAPPS==%DIGITALKNOB%\DKTestApps"
set "CMAKE_EXE=C:\PROGRA~2\CMake\bin\cmake.exe"
set MSBUILD="C:\PROGRA~2\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
set "APP=DKCore"
set "OS=win32"
set "TYPE="

echo Resetting CMake Cache . . .
echo Deleting CMake Cache files . . .
cd %DIGITALKNOB%
for /r %%i in (CMakeCache.*) do del "%%i"
echo Deleteing CMakeFiles folders . . .
for /d /r %%X in (*CMakeFiles*) do rd /s /q "%%X"

echo ****** BUILDING %APP% - %OS% ******
set APP_PATH=%DKTESTAPPS%\DKApps\%APP%
mkdir %APP_PATH%\%OS%
cd %APP_PATH%\%OS%
%CMAKE_EXE% -G "Visual Studio 16 2019" -A Win32 -DDEBUG=ON -DRELEASE=ON -DREBUILDALL=ON -DSTATIC=ON %DK%
%MSBUILD% %APP%.sln /p:Configuration=Debug
%MSBUILD% %APP%.sln /p:Configuration=Release
pause
