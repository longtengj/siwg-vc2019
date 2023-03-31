@echo off

setlocal

set SWIG_EXECUTABLE="D:\swigwin-4.1.1\swig.exe"

set BOOST_INCLUDE_DIR=F:\git\boost_1_81_0
set BOOST_LIBRARY_DIR=F:\git\boost_1_81_0\lib

set PROJECT_DIR=.
set PROJECT_NAME=example
set PYTHON_VERSION=3.7

set CMAKE_BINARY_DIR=build
set CMAKE_GENERATOR="Visual Studio 16 2019"
set CMAKE_INSTALL_PREFIX=install

set INSTALL_DIR=%PROJECT_DIR%\%CMAKE_INSTALL_PREFIX%

mkdir %INSTALL_DIR%
mkdir %PROJECT_DIR%\%CMAKE_BINARY_DIR%
pushd %PROJECT_DIR%\%CMAKE_BINARY_DIR%

cmake -G %CMAKE_GENERATOR% ^
    -DBOOST_ROOT="%BOOST_INCLUDE_DIR%" ^
    -DBOOST_LIBRARYDIR="%BOOST_LIBRARY_DIR%" ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_INSTALL_PREFIX="%INSTALL_DIR%" ^
    -DPYTHON_INCLUDE_DIR="D:/python37/Anaconda3_5.3.1/include" ^
    -DPYTHON_LIBRARY="D:/python37/Anaconda3_5.3.1/libs/python%PYTHON_VERSION%.lib" ^
    -DSWIG_EXECUTABLE=%SWIG_EXECUTABLE% ^
    ..

cmake --build . --config Release
cmake --install . --config Release

popd

pause
