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
#ifndef TMPL_TESTS_2SUM_GMP_UNIT_TEST_H
#define TMPL_TESTS_2SUM_GMP_UNIT_TEST_H
#include <gmp.h>

/*  TODO:
 *      Rewrite using long double instead of double.
 */

#define TMPL_2SUM_GMP_UNIT_TEST(type, func, inx, iny)                          \
int main(void)                                                                 \
{                                                                              \
    const type x[] = inx;                                                      \
    const type y[] = iny;                                                      \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(x);                       \
    const type eps = 2 * TMPL_EPS(x[0]);                                       \
    const double eps_squared = TMPL_CAST(eps * eps, double);                   \
    size_t n;                                                                  \
    mpf_t x_mp, y_mp, exact_mp, s_mp, e_mp, err_mp;                            \
    mpf_init2(x_mp, 1024);                                                     \
    mpf_init2(y_mp, 1024);                                                     \
    mpf_init2(exact_mp, 1024);                                                 \
    mpf_init2(s_mp, 1024);                                                     \
    mpf_init2(e_mp, 1024);                                                     \
    mpf_init2(err_mp, 1024);                                                   \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        type s, e;                                                             \
        double err;                                                            \
        tmpl_Bool x_is_nan, y_is_nan, s_is_nan, e_is_nan;                      \
        tmpl_Bool s_nan_pass, e_nan_pass, nan_pass, pass;                      \
        func(x[n], y[n], &s, &e);                                              \
        x_is_nan = TMPL_IS_NAN(x[n]);                                          \
        y_is_nan = TMPL_IS_NAN(y[n]);                                          \
        s_is_nan = TMPL_IS_NAN(s);                                             \
        e_is_nan = TMPL_IS_NAN(e);                                             \
        s_nan_pass = (!s_is_nan || (s_is_nan && (x_is_nan || y_is_nan)));      \
        e_nan_pass = (!e_is_nan || (e_is_nan && (x_is_nan || y_is_nan)));      \
        nan_pass = (s_nan_pass && e_nan_pass && (s_is_nan == e_is_nan));       \
        if (x_is_nan || y_is_nan)                                              \
        {                                                                      \
            if (nan_pass)                                                      \
                continue;                                                      \
            else                                                               \
            {                                                                  \
                puts("FAIL");                                                  \
                printf("    Input x   = %+.40E\n", TMPL_CAST(x[n], double));   \
                printf("    Input y   = %+.40E\n", TMPL_CAST(y[n], double));   \
                printf("    libtmpl s = %+.40E\n", TMPL_CAST(s, double));      \
                printf("    libtmpl e = %+.40E\n", TMPL_CAST(e, double));      \
                return -1;                                                     \
            }                                                                  \
        }                                                                      \
        mpf_set_d(x_mp, TMPL_CAST(x[n], double));                              \
        mpf_set_d(y_mp, TMPL_CAST(y[n], double));                              \
        mpf_set_d(s_mp, TMPL_CAST(s, double));                                 \
        mpf_set_d(e_mp, TMPL_CAST(e, double));                                 \
        mpf_add(exact_mp, x_mp, y_mp);                                         \
        mpf_add(err_mp, s_mp, e_mp);                                           \
        mpf_sub(err_mp, err_mp, exact_mp);                                     \
        mpf_div(err_mp, err_mp, exact_mp);                                     \
        err = mpf_get_d(err_mp);                                               \
        pass = (TMPL_ABS(err) < eps_squared);                                  \
        if (!pass)                                                             \
        {                                                                      \
            puts("FAIL");                                                      \
            printf("    Input x   = %+.40E\n", TMPL_CAST(x[n], double));       \
            printf("    Input y   = %+.40E\n", TMPL_CAST(y[n], double));       \
            printf("    libtmpl s = %+.40E\n", TMPL_CAST(s, double));          \
            printf("    libtmpl e = %+.40E\n", TMPL_CAST(e, double));          \
            printf("    Exact Sum = %+.40E\n", mpf_get_d(exact_mp));           \
            printf("    Error     = %+.40E\n", err);                           \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif
