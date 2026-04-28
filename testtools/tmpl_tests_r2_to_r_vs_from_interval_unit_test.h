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
#ifndef TMPL_TESTS_R2_TO_R_VS_FROM_INTERVAL_UNIT_TEST_H
#define TMPL_TESTS_R2_TO_R_VS_FROM_INTERVAL_UNIT_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/helper/tmpl_error_value.h>
#include <libtmpl/include/generic/tmpl_eps.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_R2_TO_R_VS_FROM_INTERVAL_UNIT_TEST                               *
 *  Purpose:                                                                  *
 *      Test functions of the form f: R^2 -> R on the square [a, b]^2.        *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The data type (float, double, int, etc.).                         *
 *      left:                                                                 *
 *          The left endpoint of the interval.                                *
 *      right:                                                                *
 *          The right endpoint of the interval.                               *
 *      f0:                                                                   *
 *          The libtmpl function being tested.                                *
 *      f1:                                                                   *
 *          The external function being compared with.                        *
 ******************************************************************************/
#define TMPL_R2_TO_R_VS_FROM_INTERVAL_UNIT_TEST(type, left, right, f0, f1)     \
int main(void)                                                                 \
{                                                                              \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    size_t n;                                                                  \
    const type start = TMPL_CAST(left, type);                                  \
    const type end = TMPL_CAST(right, type);                                   \
    const double total_number_of_samples = TMPL_CAST(NSAMPS(type), double);    \
    const double sqrt_total = sqrt(total_number_of_samples);                   \
    const size_t number_of_samples = TMPL_CAST(number_of_samples - 1, size_t); \
    const type ds = (end - start) / TMPL_CAST(number_of_samples - 1, type);    \
    const type eps = TMPL_DEFAULT_TOLERANCE * TMPL_EPS(ds);                    \
    const type real_zero = TMPL_CAST(0, type);                                 \
    volatile int flag = 0;                                                     \
    volatile type error = real_zero;                                           \
    volatile type x_bad = real_zero;                                           \
    volatile type y_bad = real_zero;                                           \
    volatile type z0_bad = real_zero;                                          \
    volatile type z1_bad = real_zero;                                          \
    TMPL_OPENMP_BASE_PRAGMA                                                    \
    for (n = zero; n < total_number_of_samples; ++n)                           \
    {                                                                          \
        if (flag)                                                              \
            continue;                                                          \
        else                                                                   \
        {                                                                      \
            const size_t x_ind = n % number_of_samples;                        \
            const size_t y_ind = n / number_of_samples;                        \
            const type x = TMPL_CAST(x_ind, type) * ds + start;                \
            const type y = TMPL_CAST(y_ind, type) * ds + start;                \
            const type z0 = f0(x, y);                                          \
            const type z1 = f1(x, y);                                          \
            const tmpl_Bool z0_is_nan = TMPL_IS_NAN(z0);                       \
            const tmpl_Bool z1_is_nan = TMPL_IS_NAN(z1);                       \
            const type err = TMPL_ERROR_VALUE(z0, z1);                         \
            if (z0_is_nan && z1_is_nan)                                        \
                continue;                                                      \
            else if ((z0_is_nan != z1_is_nan) || (err > eps))                  \
            {                                                                  \
                x_bad = x;                                                     \
                y_bad = y;                                                     \
                z0_bad = z0;                                                   \
                z1_bad = z1;                                                   \
                error = err;                                                   \
                flag = 1;                                                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    if (flag)                                                                  \
    {                                                                          \
        puts("FAIL");                                                          \
        printf("    Input x = %+.40LE\n", TMPL_CAST(x_bad, long double));      \
        printf("    Input y = %+.40LE\n", TMPL_CAST(y_bad, long double));      \
        printf("    libtmpl = %+.40LE\n", TMPL_CAST(z0_bad, long double));     \
        printf("    Other   = %+.40LE\n", TMPL_CAST(z1_bad, long double));     \
        printf("    Error   = %+.40LE\n", TMPL_CAST(error, long double));      \
    }                                                                          \
    else                                                                       \
        puts("PASS");                                                          \
    return 0;                                                                  \
}

#endif
