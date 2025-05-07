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
#ifndef TMPL_TESTS_TWOVEC_TO_TWOVEC_ARRAY_EXACT_UNIT_TEST_H
#define TMPL_TESTS_TWOVEC_TO_TWOVEC_ARRAY_EXACT_UNIT_TEST_H

#define TMPL_TWOVEC_TO_TWOVEC_ARRAY_EXACT_UNIT_TEST(type, func, inarr, outarr) \
int main(void)                                                                 \
{                                                                              \
    const type in[] = inarr;                                                   \
    const type out[] = outarr;                                                 \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in);                      \
    size_t n;                                                                  \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type output = func(&in[n]);                                      \
        const tmpl_Bool xval_is_nan = TMPL_IS_NAN(output.dat[0]);              \
        const tmpl_Bool yval_is_nan = TMPL_IS_NAN(output.dat[1]);              \
        const tmpl_Bool xout_is_nan = TMPL_IS_NAN(out[n].dat[0]);              \
        const tmpl_Bool yout_is_nan = TMPL_IS_NAN(out[n].dat[1]);              \
        const tmpl_Bool x_equal = (output.dat[0] == out[n].dat[0]);            \
        const tmpl_Bool y_equal = (output.dat[1] == out[n].dat[1]);            \
        const tmpl_Bool xnan_pass = (xval_is_nan && xout_is_nan);              \
        const tmpl_Bool ynan_pass = (yval_is_nan && yout_is_nan);              \
        const tmpl_Bool xnan_equal = (xval_is_nan == xout_is_nan);             \
        const tmpl_Bool ynan_equal = (yval_is_nan == yout_is_nan);             \
        const tmpl_Bool x_pass = (xnan_pass || (x_equal && xnan_equal));       \
        const tmpl_Bool y_pass = (ynan_pass || (y_equal && ynan_equal));       \
        if ((!x_pass) || (!y_pass))                                            \
        {                                                                      \
            const long double x = TMPL_CAST(in[n].dat[0], long double);        \
            const long double y = TMPL_CAST(in[n].dat[1], long double);        \
            const long double xl = TMPL_CAST(output.dat[0], long double);      \
            const long double yl = TMPL_CAST(output.dat[1], long double);      \
            const long double xc = TMPL_CAST(out[n].dat[0], long double);      \
            const long double yc = TMPL_CAST(out[n].dat[1], long double);      \
            const long double xerr = TMPL_ERROR_VALUE(xl, xc);                 \
            const long double yerr = TMPL_ERROR_VALUE(yl, yc);                 \
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
