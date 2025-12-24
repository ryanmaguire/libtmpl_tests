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
#ifndef TMPL_TESTS_2OP_GMP_UNIT_TEST_H
#define TMPL_TESTS_2OP_GMP_UNIT_TEST_H

#include <gmp.h>
#include <string.h>
#include "tmpl_tests_mpf_get_ld.h"
#include "tmpl_tests_mpf_set_ld.h"

#define TMPL_2OP_GMP_UNIT_TEST(type, func, mpf_op, inx, iny)                   \
int main(void)                                                                 \
{                                                                              \
    const type x[] = inx;                                                      \
    const type y[] = iny;                                                      \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(x);                       \
    const long double eps = TMPL_CAST(2 * TMPL_EPS(x[0]), long double);        \
    const long double eps_squared = eps * eps;                                 \
    size_t n;                                                                  \
    type s, e;                                                                 \
    long double err, eval;                                                     \
    tmpl_Bool x_is_nan, y_is_nan, x_is_inf, y_is_inf;                          \
    mpf_t x_mp, y_mp, exact_mp, s_mp, e_mp, err_mp;                            \
    mpf_init2(x_mp, 1024);                                                     \
    mpf_init2(y_mp, 1024);                                                     \
    mpf_init2(exact_mp, 1024);                                                 \
    mpf_init2(s_mp, 1024);                                                     \
    mpf_init2(e_mp, 1024);                                                     \
    mpf_init2(err_mp, 1024);                                                   \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        func(x[n], y[n], &s, &e);                                              \
        x_is_nan = TMPL_IS_NAN(x[n]);                                          \
        y_is_nan = TMPL_IS_NAN(y[n]);                                          \
        if (x_is_nan || y_is_nan)                                              \
        {                                                                      \
            if (TMPL_IS_NAN(s) && TMPL_IS_NAN(e))                              \
                continue;                                                      \
            else                                                               \
                goto FAIL;                                                     \
        }                                                                      \
        x_is_inf = TMPL_IS_INF(x[n]);                                          \
        y_is_inf = TMPL_IS_INF(y[n]);                                          \
        if (x_is_inf || y_is_inf)                                              \
        {                                                                      \
            if (!TMPL_IS_NAN(e))                                               \
                goto FAIL;                                                     \
            if (TMPL_IS_NAN(s))                                                \
            {                                                                  \
                if (x_is_inf && y_is_inf && (x[n] != y[n]))                    \
                    continue;                                                  \
                else                                                           \
                    goto FAIL;                                                 \
            }                                                                  \
            if (TMPL_IS_INF(s))                                                \
                continue;                                                      \
            else                                                               \
                goto FAIL;                                                     \
        }                                                                      \
        tmpl_tests_mpf_set_ld(x_mp, TMPL_CAST(x[n], long double));             \
        tmpl_tests_mpf_set_ld(y_mp, TMPL_CAST(y[n], long double));             \
        tmpl_tests_mpf_set_ld(s_mp, TMPL_CAST(s, long double));                \
        tmpl_tests_mpf_set_ld(e_mp, TMPL_CAST(e, long double));                \
        mpf_op(exact_mp, x_mp, y_mp);                                          \
        mpf_op(err_mp, s_mp, e_mp);                                            \
        mpf_sub(err_mp, err_mp, exact_mp);                                     \
        mpf_div(err_mp, err_mp, exact_mp);                                     \
        eval = tmpl_tests_mpf_get_ld(exact_mp);                                \
        err = tmpl_tests_mpf_get_ld(err_mp);                                   \
        if (TMPL_ABS(err) > eps_squared)                                       \
        {                                                                      \
            puts("FAIL");                                                      \
            printf("    Input x   = %+.40LE\n", TMPL_CAST(x[n], long double)); \
            printf("    Input y   = %+.40LE\n", TMPL_CAST(y[n], long double)); \
            printf("    libtmpl s = %+.40LE\n", TMPL_CAST(s, long double));    \
            printf("    libtmpl e = %+.40LE\n", TMPL_CAST(e, long double));    \
            printf("    Exact Sum = %+.40LE\n", eval);                         \
            printf("    Error     = %+.40LE\n", err);                          \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
FAIL:                                                                          \
    puts("FAIL");                                                              \
    printf("    x = %+.40LE\n", TMPL_CAST(x[n], long double));                 \
    printf("    y = %+.40LE\n", TMPL_CAST(y[n], long double));                 \
    printf("    s = %+.40LE\n", TMPL_CAST(s, long double));                    \
    printf("    e = %+.40LE\n", TMPL_CAST(e, long double));                    \
    return -1;                                                                 \
}

#endif
