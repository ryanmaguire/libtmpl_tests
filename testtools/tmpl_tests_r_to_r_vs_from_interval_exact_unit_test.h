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
#ifndef TMPL_TESTS_R_TO_R_VS_FROM_INTERVAL_EXACT_UNIT_TEST_H
#define TMPL_TESTS_R_TO_R_VS_FROM_INTERVAL_EXACT_UNIT_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include <libtmpl/include/helper/tmpl_error_value.h>
#include <stddef.h>
#include <stdio.h>

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_R_TO_R_VS_FROM_INTERVAL_EXACT_UNIT_TEST                          *
 *  Purpose:                                                                  *
 *      Test functions of the form f: R -> R across an interval [a, b].       *
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
#define TMPL_R_TO_R_VS_FROM_INTERVAL_EXACT_UNIT_TEST(type, left, right, f0, f1)\
int main(void)                                                                 \
{                                                                              \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    size_t n;                                                                  \
    const type start = TMPL_CAST(left, type);                                  \
    const type end = TMPL_CAST(right, type);                                   \
    const size_t number_of_samples = NSAMPS(type);                             \
    const type dx = (end - start) / TMPL_CAST(number_of_samples - 1, type);    \
    volatile int flag = 0;                                                     \
    volatile long double error = 0.0L;                                         \
    volatile long double x_bad = 0.0L;                                         \
    volatile long double y_bad = 0.0L;                                         \
    volatile long double z_bad = 0.0L;                                         \
    TMPL_OPENMP_BASE_PRAGMA                                                    \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        if (flag)                                                              \
            continue;                                                          \
        else                                                                   \
        {                                                                      \
            const type x = TMPL_CAST(n, type) * dx + start;                    \
            const type y = f0(x);                                              \
            const type z = f1(x);                                              \
            const tmpl_Bool y_is_nan = TMPL_IS_NAN(y);                         \
            const tmpl_Bool z_is_nan = TMPL_IS_NAN(z);                         \
            if (y_is_nan && z_is_nan)                                          \
                continue;                                                      \
            else if ((y_is_nan != z_is_nan) || (y != z))                       \
            {                                                                  \
                x_bad = TMPL_CAST(x, long double);                             \
                y_bad = TMPL_CAST(y, long double);                             \
                z_bad = TMPL_CAST(z, long double);                             \
                error = TMPL_ERROR_VALUE(y_bad, z_bad);                        \
                flag = 1;                                                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    if (flag)                                                                  \
    {                                                                          \
        puts("FAIL");                                                          \
        printf("    Input   = %+.40LE\n", x_bad);                              \
        printf("    libtmpl = %+.40LE\n", y_bad);                              \
        printf("    Other   = %+.40LE\n", z_bad);                              \
        printf("    Error   = %+.40LE\n", error);                              \
    }                                                                          \
    else                                                                       \
        puts("PASS");                                                          \
    return 0;                                                                  \
}

#endif

