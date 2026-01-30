/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl_tests.                                       *
 *                                                                            *
 *  libtmpl_tests is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl_tests is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl_tests.  If not, see <https://www.gnu.org/licenses/>.   *
 ******************************************************************************/
#ifndef TMPL_TESTS_C_TO_C_VS_FROM_ARRAY_UNIT_TEST_H
#define TMPL_TESTS_C_TO_C_VS_FROM_ARRAY_UNIT_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/helper/tmpl_array_size.h>
#include <libtmpl/include/helper/tmpl_error_value.h>
#include <libtmpl/include/generic/tmpl_eps.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include <cstddef>
#include <cstdio>
#include <complex>

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_C_TO_C_ARRAY_UNIT_TEST                                           *
 *  Purpose:                                                                  *
 *      Test functions of the form f: R -> R over a given array.              *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The data type (tmpl_ComplexDouble, etc.).                         *
 *      ftype:                                                                *
 *          The float type (double, etc.).                                    *
 *      func0:                                                                *
 *          The libtmpl function being tested.                                *
 *      func1:                                                                *
 *          The function being tested against.                                *
 *      indata:                                                               *
 *          The input array.                                                  *
 ******************************************************************************/
#define TMPL_C_TO_C_VS_FROM_ARRAY_UNIT_TEST(type, ftype, func0, func1, inarr)  \
typedef std::complex<ftype> ctype;                                             \
int main(void)                                                                 \
{                                                                              \
    const type in[] = inarr;                                                   \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in);                      \
    const ftype eps = 2 * TMPL_EPS(in[0].dat[0]);                              \
    size_t n;                                                                  \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type output = func0(in[n]);                                      \
        const ctype inval = ctype(in[n].dat[0], in[n].dat[1]);                 \
        const ctype outval = func1(inval);                                     \
        const bool xval_is_nan = TMPL_IS_NAN(output.dat[0]);                   \
        const bool yval_is_nan = TMPL_IS_NAN(output.dat[1]);                   \
        const bool xout_is_nan = TMPL_IS_NAN(outval.real());                   \
        const bool yout_is_nan = TMPL_IS_NAN(outval.imag());                   \
        const ftype x_err = TMPL_ERROR_VALUE(output.dat[0], outval.real());    \
        const ftype y_err = TMPL_ERROR_VALUE(output.dat[1], outval.imag());    \
        const bool x_good = (x_err < eps);                                     \
        const bool y_good = (y_err < eps);                                     \
        const bool xnan_pass = (xval_is_nan && xout_is_nan);                   \
        const bool ynan_pass = (yval_is_nan && yout_is_nan);                   \
        const bool xnan_equal = (xval_is_nan == xout_is_nan);                  \
        const bool ynan_equal = (yval_is_nan == yout_is_nan);                  \
        const bool x_pass = (xnan_pass || (x_good && xnan_equal));             \
        const bool y_pass = (ynan_pass || (y_good && ynan_equal));             \
        if ((!x_pass) || (!y_pass))                                            \
        {                                                                      \
            const long double x = TMPL_CAST(in[n].dat[0], long double);        \
            const long double y = TMPL_CAST(in[n].dat[1], long double);        \
            const long double xl = TMPL_CAST(output.dat[0], long double);      \
            const long double yl = TMPL_CAST(output.dat[1], long double);      \
            const long double xc = TMPL_CAST(outval.real(), long double);      \
            const long double yc = TMPL_CAST(outval.imag(), long double);      \
            const long double xerr = TMPL_CAST(x_err, long double);            \
            const long double yerr = TMPL_CAST(y_err, long double);            \
            puts("FAIL");                                                      \
            printf("    Input x   = %+.40LE\n", x);                            \
            printf("    Input y   = %+.40LE\n", y);                            \
            printf("    libtmpl x = %+.40LE\n", xl);                           \
            printf("    libtmpl y = %+.40LE\n", yl);                           \
            printf("    Other x   = %+.40LE\n", xc);                           \
            printf("    Other y   = %+.40LE\n", yc);                           \
            printf("    Error x   = %+.40LE\n", xerr);                         \
            printf("    Error y   = %+.40LE\n", yerr);                         \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif
