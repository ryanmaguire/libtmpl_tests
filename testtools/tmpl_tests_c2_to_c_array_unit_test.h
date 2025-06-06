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
#ifndef TMPL_TESTS_C2_TO_C_ARRAY_UNIT_TEST_H
#define TMPL_TESTS_C2_TO_C_ARRAY_UNIT_TEST_H

#define TMPL_C2_TO_C_ARRAY_UNIT_TEST(type, ftype, func, inarr0, inarr1, outarr)\
int main(void)                                                                 \
{                                                                              \
    const type in0[] = inarr0;                                                 \
    const type in1[] = inarr1;                                                 \
    const type out[] = outarr;                                                 \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in0);                     \
    const ftype eps = 2 * TMPL_EPS(out[0].dat[0]);                             \
    size_t n;                                                                  \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type output = func(in0[n], in1[n]);                              \
        const tmpl_Bool xval_is_nan = TMPL_IS_NAN(output.dat[0]);              \
        const tmpl_Bool yval_is_nan = TMPL_IS_NAN(output.dat[1]);              \
        const tmpl_Bool xout_is_nan = TMPL_IS_NAN(out[n].dat[0]);              \
        const tmpl_Bool yout_is_nan = TMPL_IS_NAN(out[n].dat[1]);              \
        const ftype x_err = TMPL_ERROR_VALUE(output.dat[0], out[n].dat[0]);    \
        const ftype y_err = TMPL_ERROR_VALUE(output.dat[1], out[n].dat[1]);    \
        const tmpl_Bool x_good = (x_err < eps);                                \
        const tmpl_Bool y_good = (y_err < eps);                                \
        const tmpl_Bool xnan_pass = (xval_is_nan && xout_is_nan);              \
        const tmpl_Bool ynan_pass = (yval_is_nan && yout_is_nan);              \
        const tmpl_Bool xnan_equal = (xval_is_nan == xout_is_nan);             \
        const tmpl_Bool ynan_equal = (yval_is_nan == yout_is_nan);             \
        const tmpl_Bool x_pass = (xnan_pass || (x_good && xnan_equal));        \
        const tmpl_Bool y_pass = (ynan_pass || (y_good && ynan_equal));        \
        if ((!x_pass) || (!y_pass))                                            \
        {                                                                      \
            const long double x0 = TMPL_CAST(in0[n].dat[0], long double);      \
            const long double y0 = TMPL_CAST(in0[n].dat[1], long double);      \
            const long double x1 = TMPL_CAST(in1[n].dat[0], long double);      \
            const long double y1 = TMPL_CAST(in1[n].dat[1], long double);      \
            const long double xl = TMPL_CAST(output.dat[0], long double);      \
            const long double yl = TMPL_CAST(output.dat[1], long double);      \
            const long double xc = TMPL_CAST(out[n].dat[0], long double);      \
            const long double yc = TMPL_CAST(out[n].dat[1], long double);      \
            const long double xerr = TMPL_ERROR_VALUE(xl, xc);                 \
            const long double yerr = TMPL_ERROR_VALUE(yl, yc);                 \
            puts("FAIL");                                                      \
            printf("    Input x0  = %+.40LE\n", x0);                           \
            printf("    Input y0  = %+.40LE\n", y0);                           \
            printf("    Input x1  = %+.40LE\n", x1);                           \
            printf("    Input y1  = %+.40LE\n", y1);                           \
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
