<!---
    LICENSE

    This file is part of libtmpl_tests.

    libtmpl_tests is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libtmpl_tests is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libtmpl_tests.  If not, see <https://www.gnu.org/licenses/>.

    AUTHOR
        Ryan Maguire
--->

# libtmpl_tests
Unit and performance tests for libtmpl.

# Dependencies
`libtmpl` has very few dependencies. Namely, a `C` compiler supporting any of
the major standards (`C89`, `C99`, `C11`, `C17`, or `C23`) and a small portion
of the `C standard library.

These tests, on the other hand, use lots of external libraries to compare
functions with. They also use modern `C` features (like `_Generic`), and
`C++` standard library functions are used as well.
To run every test, you will need:

- 1. `libtmpl`.
- 2. A `C` compiler with the standard library and `C11` support.
- 3. A `C++` compiler with the standard library and `C++17` support.
- 4. GMP (The GNU Multi-Precision Arithmetic Library).
- 5. GSL (The GNU Scientific Library).
- 6. FFTW (The Fastest Fourier Transform in the West).
- 7. `libquadmath` (GNU Quadruple Precision Math Library).
- 7. `libcerf` (Error Function Library)
- 8. `linasm` (Assembly Math Library for `x86-64`).
- 9. Boost Libraries
    - 10a. `boost/math/special_functions`
    - 10b. `boost/math/tools/polynomial`
    - 10c. `boost/integer`
    - 10d. `boost/rational`

# License
    libtmpl_tests is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libtmpl_tests is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libtmpl_tests.  If not, see <https://www.gnu.org/licenses/>.
