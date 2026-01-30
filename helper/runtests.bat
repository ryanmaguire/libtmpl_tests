::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                  LICENSE                                   ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::  This file is part of libtmpl_tests.                                       ::
::                                                                            ::
::  libtmpl_tests is free software: you can redistribute it and/or modify     ::
::  it under the terms of the GNU General Public License as published by      ::
::  the Free Software Foundation, either version 3 of the License, or         ::
::  (at your option) any later version.                                       ::
::                                                                            ::
::  libtmpl_tests is distributed in the hope that it will be useful,          ::
::  but WITHOUT ANY WARRANTY; without even the implied warranty of            ::
::  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             ::
::  GNU General Public License for more details.                              ::
::                                                                            ::
::  You should have received a copy of the GNU General Public License         ::
::  along with libtmpl_tests.  If not, see <https://www.gnu.org/licenses/>.   ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::  Author:     Ryan Maguire                                                  ::
::  Date:       January 23, 2025                                              ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
@ECHO OFF
SETLOCAL EnableDelayedExpansion

:: Default values, use MSVC (cl.exe).
SET "CC=cl"
SET "CPP=cl"
SET "ExtraArgs="
SET "TYPE=unit"

:: Location of the header files installed by vcpkg.
SET "VCPATH=C:\libtmpl_tests\vcpkg_installed\x64-windows-static\include"
SET "VCLIBS=C:\libtmpl_tests\vcpkg_installed\x64-windows-static\lib"

:: C Compiler arguments. Unit tests use _Generic and variadic macros to
:: simplify things (libtmpl itself does not, it is C89 compliant). Need to
:: enable std:c11 for things to compile correctly.
SET "CARGS=/std:c11 /O2 /MD /IC:\ /I%VCPATH%"
SET "CLIBRARIES=%VCLIBS%\gmp.lib %VCLIBS%\gsl.lib %VCLIBS%\gslcblas.lib"

:: C++ unit tests makes use of C++17 standard library functions. Enable these.
SET "CPPARGS=/std:c++17 /O2 /IC:\ /I%VCPATH%"
set "CPPLIBRARIES=%VCLIBS%\cerfcpp.lib %VCLIBS%\gmpxx.lib"

:: Linker arguments (the last bit silences the compiler / linker).
SET "LARGS=C:\libtmpl\libtmpl.lib /link /out:main.exe"
SET "CLARGS=%CLIBRARIES% %LARGS%"
SET "CPPLARGS=%CPPLIBRARIES% %LARGS%"

:: Parse command-line arguments.
:PARSE_ARGS
IF "%~1"=="" GOTO DONE_ARGS

ECHO %~1 | FINDSTR /b /c:"-cc=" >NUL
IF NOT ERRORLEVEL 1 (
    FOR /f "tokens=2 delims==" %%a IN ("%~1") DO SET "CC=%%a"
    SHIFT
    GOTO PARSE_ARGS
)

ECHO %~1 | FINDSTR /b /c:"-cpp=" > NUL
IF NOT ERRORLEVEL 1 (
    FOR /f "tokens=2 delims==" %%a IN ("%~1") DO SET "CPP=%%a"
    SHIFT
    GOTO PARSE_ARGS
)

ECHO %~1 | FINDSTR /b /c:"-type=" > NUL
IF NOT ERRORLEVEL 1 (
    FOR /f "tokens=2 delims==" %%a IN ("%~1") DO SET "TYPE=%%a"
    SHIFT
    GOTO PARSE_ARGS
)

:: Any other arguments go to ExtraArgs.
SET "ExtraArgs=!ExtraArgs! %~1"
SHIFT
GOTO PARSE_ARGS

:DONE_ARGS

:: Compile and run C files.
FOR /f "delims=" %%f IN ('dir /b /s "*%TYPE%*.c"') DO (
    CALL "%CC%" !ExtraArgs! %CARGS% "%%f" %CLARGS% >nul 2>&1
    IF ERRORLEVEL 1 (
        ECHO [FAILED TO COMPILE] %%f
    ) ELSE (
        < NUL SET /p ="%%f: "
        CALL main.exe
        DEL /f /q main.exe *.obj
    )
)

:: Compile and run C++ files.
FOR /f "delims=" %%f IN ('dir /b /s "*%TYPE%*.cpp"') DO (
    CALL "%CPP%" !ExtraArgs! %CPPARGS% "%%f" %CPPLARGS% >nul 2>&1
    IF ERRORLEVEL 1 (
        ECHO [FAILED TO COMPILE] %%f
    ) ELSE (
        < NUL SET /p ="%%f: "
        CALL main.exe
        DEL /f /q main.exe *.obj
    )
)

ENDLOCAL
