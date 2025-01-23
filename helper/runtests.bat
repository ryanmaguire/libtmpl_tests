::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                 LICENSE                                    ::
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

:: Compiler arguments. Unit tests used _Generic and variadic macros to
:: simplify things (libtmpl itself does not, it is C89 compliant). Need to
:: enable std:c11 for things to compile correctly.
SET CARGS=/std:c11 /O2 /IC:\

:: Linker / output arguments.
SET LARGS=/link /out:main.exe

FOR /D %%d IN (.\*) DO (
    FOR %%i IN (%%d\*unit_test*.c) DO (
        cl %CARGS% %%i C:\libtmpl\libtmpl.lib %LARGS%
        ECHO %%i: >> results.txt
        main.exe >> results.txt
        DEL *.obj *.exe
    )
)
