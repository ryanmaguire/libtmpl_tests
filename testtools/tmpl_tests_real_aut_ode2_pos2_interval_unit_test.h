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
#ifndef TMPL_TESTS_REAL_AUT_ODE2_2POS_INTERVAL_UNIT_TEST_H
#define TMPL_TESTS_REAL_AUT_ODE2_2POS_INTERVAL_UNIT_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/helper/tmpl_error_value.h>
#include <libtmpl/include/helper/tmpl_max.h>
#include <libtmpl/include/generic/tmpl_eps.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include <stddef.h>
#include <stdio.h>

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_REAL_AUT_ODE_INTERVAL_UNIT_TEST                                  *
 *  Purpose:                                                                  *
 *      Test autonomous numerical ODE methods.                                *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The data type (float, double, int, etc.).                         *
 *      left:                                                                 *
 *          The left endpoint of the interval.                                *
 *      right:                                                                *
 *          The right endpoint of the interval.                               *
 *      sol:                                                                  *
 *          The numerical method of solution (Euler, RK4, etc.).              *
 *      f:                                                                    *
 *          The autonomous ODE formula.                                       *
 *      g:                                                                    *
 *          The exact solution.                                               *
 *      ord:                                                                  *
 *          The order of the error for the numerical method.                  *
 ******************************************************************************/
#define TMPL_REAL_AUT_ODE2_2POS_INTERVAL_UNIT_TEST(type, l, r, sol, f, g, ord) \
int main(void)                                                                 \
{                                                                              \
    const size_t one = TMPL_CAST(1, size_t);                                   \
    size_t n;                                                                  \
    const type start = TMPL_CAST(l, type);                                     \
    const type end = TMPL_CAST(r, type);                                       \
    const size_t number_of_samples = 8192;                                     \
    const type dx = (end - start) / TMPL_CAST(number_of_samples, type);        \
    const long double ode_eps_ld = powl(TMPL_CAST(4 * dx, long double), ord);  \
    const type ode_eps = TMPL_CAST(ode_eps_ld, type);                          \
    const type min_eps = TMPL_DEFAULT_TOLERANCE * TMPL_EPS(dx);                \
    const type eps = TMPL_MAX(ode_eps, min_eps);                               \
    type z_old0 = g(start);                                                    \
    type z_old1 = z_old0;                                                      \
    for (n = one; n <= number_of_samples; ++n)                                 \
    {                                                                          \
        const type x = TMPL_CAST(n, type) * dx + start;                        \
        const type y = sol(f, z_old0, z_old1, dx);                             \
        const type z = g(x);                                                   \
        const tmpl_Bool y_is_nan = TMPL_IS_NAN(y);                             \
        const tmpl_Bool z_is_nan = TMPL_IS_NAN(z);                             \
        const type err = TMPL_ERROR_VALUE(y, z);                               \
        z_old0 = z_old1;                                                       \
        z_old1 = z;                                                            \
        if (y_is_nan && z_is_nan)                                              \
            continue;                                                          \
        else if ((y_is_nan != z_is_nan) || (err > eps))                        \
        {                                                                      \
            puts("FAIL");                                                      \
            printf("    Input   = %+.40LE\n", TMPL_CAST(x, long double));      \
            printf("    libtmpl = %+.40LE\n", TMPL_CAST(y, long double));      \
            printf("    Other   = %+.40LE\n", TMPL_CAST(z, long double));      \
            printf("    Error   = %+.40LE\n", TMPL_CAST(err, long double));    \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif
