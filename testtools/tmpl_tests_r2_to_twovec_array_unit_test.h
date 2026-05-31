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
#ifndef TMPL_TESTS_R2_TO_TWOVEC_ARRAY_UNIT_TEST_H
#define TMPL_TESTS_R2_TO_TWOVEC_ARRAY_UNIT_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/helper/tmpl_array_size.h>
#include <libtmpl/include/helper/tmpl_error_value.h>
#include <libtmpl/include/generic/tmpl_eps.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_R2_TO_TWOVEC_ARRAY_UNIT_TEST                                     *
 *  Purpose:                                                                  *
 *      Test functions of the form f: R^2 -> R^2 over a given array.          *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The data type (float, double, int, etc.).                         *
 *      vtype:                                                                *
 *          The vector type (tmpl_ComplexDouble, tmpl_TwoVectorDouble, etc.). *
 *      func:                                                                 *
 *          The libtmpl function being tested.                                *
 *      indata:                                                               *
 *          The input array.                                                  *
 *      outdata:                                                              *
 *          The output array. To pass we need |func(indata) - outdata| small. *
 ******************************************************************************/
#define TMPL_R2_TO_TWOVEC_ARRAY_UNIT_TEST(type, vtype, func, indata, outdata)  \
int main(void)                                                                 \
{                                                                              \
    struct real2 {type x, y;} in[] = indata;                                   \
    const vtype out[] = outdata;                                               \
    const type eps = TMPL_DEFAULT_TOLERANCE * TMPL_EPS(in[0].x);               \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in);                      \
    size_t n;                                                                  \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const vtype output = func(in[n].x, in[n].y);                           \
        const type xerr = TMPL_ERROR_VALUE(output.dat[0], out[n].dat[0]);      \
        const type yerr = TMPL_ERROR_VALUE(output.dat[1], out[n].dat[1]);      \
        const tmpl_Bool x_val_is_nan = TMPL_IS_NAN(output.dat[0]);             \
        const tmpl_Bool y_val_is_nan = TMPL_IS_NAN(output.dat[1]);             \
        const tmpl_Bool x_out_is_nan = TMPL_IS_NAN(out[n].dat[0]);             \
        const tmpl_Bool y_out_is_nan = TMPL_IS_NAN(out[n].dat[1]);             \
        if ((x_val_is_nan == x_out_is_nan) && (y_val_is_nan == y_out_is_nan))  \
            continue;                                                          \
        else if ((xerr > eps) || (yerr > eps))                                 \
        {                                                                      \
            const long double xin = TMPL_CAST(in[n].x, long double);           \
            const long double yin = TMPL_CAST(in[n].y, long double);           \
            const long double xout = TMPL_CAST(output.dat[0], long double);    \
            const long double yout = TMPL_CAST(output.dat[1], long double);    \
            const long double xother = TMPL_CAST(out[n].dat[0], long double);  \
            const long double yother = TMPL_CAST(out[n].dat[0], long double);  \
            puts("FAIL");                                                      \
            printf("    Input x = %+.40LE\n", xin);                            \
            printf("    Input y = %+.40LE\n", yin);                            \
            printf("    libtmpl x = %+.40LE\n", xout);                         \
            printf("    libtmpl y = %+.40LE\n", yout);                         \
            printf("    Other x = %+.40LE\n", xother);                         \
            printf("    Other y = %+.40LE\n", yother);                         \
            printf("    x Error = %+.40LE\n", TMPL_CAST(xerr, long double));   \
            printf("    y Error = %+.40LE\n", TMPL_CAST(yerr, long double));   \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif
