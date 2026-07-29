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
#ifndef TMPL_TESTS_2OP_VS_GMP_INTERVAL_UNIT_TEST_H
#define TMPL_TESTS_2OP_VS_GMP_INTERVAL_UNIT_TEST_H

#ifndef NO_GMP

#include <gmp.h>
#include <string.h>
#include <libtmpl/include/generic/tmpl_eps.h>
#include <libtmpl/include/generic/tmpl_is_inf.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include "tmpl_tests_mpf_get_ld.h"
#include "tmpl_tests_mpf_set_ld.h"
#include "tmpl_tests_dd_create.h"

#define TMPL_2OP_VS_GMP_INTERVAL_UNIT_TEST(dtype, func, mpf_op)                \
int main(void)                                                                 \
{                                                                              \
    const dtype start = TMPL_CAST(-1, dtype);                                  \
    const dtype end = TMPL_CAST(1, dtype);                                     \
    const mp_bitcnt_t number_of_bits = 512;                                    \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const long double len_ld = TMPL_CAST(TMPL_NSAMPS, long double);            \
    const long double num_samps_ld = sqrtl(len_ld);                            \
    const size_t number_of_samples = TMPL_CAST(num_samps_ld, size_t);          \
    const dtype eps_type = TMPL_DEFAULT_TOLERANCE * TMPL_EPS(start);           \
    const long double eps = TMPL_CAST(eps_type, long double);                  \
    const long double eps_squared = eps * eps;                                 \
    const dtype ds = (end - start) / TMPL_CAST(number_of_samples - 1, dtype);  \
    size_t xhi, xlo;                                                           \
    mpf_t xhi_mp, xlo_mp, x_mp;                                                \
    mpf_t exact_mp, out_hi_mp, out_lo_mp, out_mp, err_mp;                      \
    mpf_init2(xhi_mp, number_of_bits);                                         \
    mpf_init2(xlo_mp, number_of_bits);                                         \
    mpf_init2(x_mp, number_of_bits);                                           \
    mpf_init2(exact_mp, number_of_bits);                                       \
    mpf_init2(out_hi_mp, number_of_bits);                                      \
    mpf_init2(out_lo_mp, number_of_bits);                                      \
    mpf_init2(out_mp, number_of_bits);                                         \
    mpf_init2(err_mp, number_of_bits);                                         \
    for (xhi = zero; xhi < number_of_samples; ++xhi)                           \
    {                                                                          \
        const dtype xhi_val = start + TMPL_CAST(xhi, dtype) * ds;              \
        const long double xhi_ld = TMPL_CAST(xhi_val, long double);            \
        tmpl_tests_mpf_set_ld(xhi_mp, xhi_ld);                                 \
        for (xlo = zero; xlo < number_of_samples; ++xlo)                       \
        {                                                                      \
            dtype out_hi, out_lo;                                              \
            long double out_hi_ld, out_lo_ld;                                  \
            long double err;                                                   \
            const dtype xlo_tmp = start + TMPL_CAST(xlo, dtype) * ds;          \
            const dtype xlo_val = xlo_tmp * TMPL_EPS(xlo_tmp);                 \
            const long double xlo_ld = TMPL_CAST(xlo_val, long double);        \
            tmpl_tests_mpf_set_ld(xlo_mp, xlo_ld);                             \
            func(xhi_val, xlo_val, &out_hi, &out_lo);                          \
            out_hi_ld = TMPL_CAST(out_hi, long double);                        \
            out_lo_ld = TMPL_CAST(out_lo, long double);                        \
            tmpl_tests_mpf_set_ld(out_hi_mp, out_hi_ld);                       \
            tmpl_tests_mpf_set_ld(out_lo_mp, out_lo_ld);                       \
            mpf_add(out_mp, out_hi_mp, out_lo_mp);                             \
            mpf_op(exact_mp, xhi_mp, xlo_mp);                                  \
            mpf_sub(err_mp, out_mp, exact_mp);                                 \
            if (mpf_sgn(exact_mp) != 0)                                        \
                mpf_div(err_mp, err_mp, exact_mp);                             \
            err = tmpl_tests_mpf_get_ld(err_mp);                               \
            if (TMPL_ABS(err) > eps_squared)                                   \
            {                                                                  \
                long double eval = tmpl_tests_mpf_get_ld(exact_mp);            \
                puts("FAIL");                                                  \
                printf("    Input x hi = %+.50LE\n", xhi_ld);                  \
                printf("    Input x lo = %+.50LE\n", xlo_ld);                  \
                printf("    libtmpl hi = %+.50LE\n", out_hi_ld);               \
                printf("    libtmpl lo = %+.50LE\n", out_lo_ld);               \
                printf("    Exact      = %+.50LE\n", eval);                    \
                printf("    Error      = %+.50LE\n", err);                     \
                return -1;                                                     \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif

#endif
