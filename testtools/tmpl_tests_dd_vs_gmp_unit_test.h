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
#ifndef TMPL_TESTS_DD_VS_GMP_UNIT_TEST_H
#define TMPL_TESTS_DD_VS_GMP_UNIT_TEST_H

#ifndef NO_GMP

#include <gmp.h>
#include <string.h>
#include <libtmpl/include/generic/tmpl_eps.h>
#include <libtmpl/include/generic/tmpl_is_inf.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include "tmpl_tests_mpf_get_ld.h"
#include "tmpl_tests_mpf_set_ld.h"
#include "tmpl_tests_dd_create.h"

#define TMPL_DD_VS_GMP_UNIT_TEST(ddtype, dtype, func, mpf_op)                  \
int main(void)                                                                 \
{                                                                              \
    const dtype start = TMPL_CAST(-1, dtype);                                  \
    const dtype end = TMPL_CAST(1, dtype);                                     \
    const mp_bitcnt_t number_of_bits = 512;                                    \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const long double len_ld = TMPL_CAST(TMPL_NSAMPS, long double);            \
    const long double num_samps_ld = sqrtl(sqrtl(len_ld));                     \
    const size_t number_of_samples = TMPL_CAST(num_samps_ld, size_t);          \
    const dtype eps_type = TMPL_DEFAULT_TOLERANCE * TMPL_EPS(start);           \
    const long double eps = TMPL_CAST(eps_type, long double);                  \
    const long double eps_squared = eps * eps;                                 \
    const dtype ds = (end - start) / TMPL_CAST(number_of_samples - 1, dtype);  \
    size_t xhi, xlo, yhi, ylo;                                                 \
    long double err;                                                           \
    mpf_t xhi_mp, xlo_mp, x_mp, yhi_mp, ylo_mp, y_mp;                          \
    mpf_t exact_mp, out_hi_mp, out_lo_mp, out_mp, err_mp, tmp_mp;              \
    mpf_init2(xhi_mp, number_of_bits);                                         \
    mpf_init2(xlo_mp, number_of_bits);                                         \
    mpf_init2(x_mp, number_of_bits);                                           \
    mpf_init2(yhi_mp, number_of_bits);                                         \
    mpf_init2(ylo_mp, number_of_bits);                                         \
    mpf_init2(y_mp, number_of_bits);                                           \
    mpf_init2(exact_mp, number_of_bits);                                       \
    mpf_init2(out_hi_mp, number_of_bits);                                      \
    mpf_init2(out_lo_mp, number_of_bits);                                      \
    mpf_init2(out_mp, number_of_bits);                                         \
    mpf_init2(err_mp, number_of_bits);                                         \
    mpf_init2(tmp_mp, number_of_bits);                                         \
    for (xhi = zero; xhi < number_of_samples; ++xhi)                           \
    {                                                                          \
        const dtype xhi_val = start + TMPL_CAST(xhi, dtype) * ds;              \
        for (xlo = zero; xlo < number_of_samples; ++xlo)                       \
        {                                                                      \
            const dtype xlo_tmp = start + TMPL_CAST(xlo, dtype) * ds;          \
            const dtype xlo_val = xlo_tmp * TMPL_EPS(xlo_tmp);                 \
            const ddtype x = TMPL_DD_CREATE(xhi_val, xlo_val);                 \
            const long double xhi_ld = TMPL_CAST(x.dat[0], long double);       \
            const long double xlo_ld = TMPL_CAST(x.dat[1], long double);       \
            tmpl_tests_mpf_set_ld(xhi_mp, xhi_ld);                             \
            tmpl_tests_mpf_set_ld(xlo_mp, xlo_ld);                             \
            mpf_add(x_mp, xhi_mp, xlo_mp);                                     \
            for (yhi = zero; yhi < number_of_samples; ++yhi)                   \
            {                                                                  \
                const dtype yhi_val = start + TMPL_CAST(yhi, dtype) * ds;      \
                for (ylo = zero; ylo < number_of_samples; ++ylo)               \
                {                                                              \
                    const dtype ylo_tmp = start + TMPL_CAST(ylo, dtype) * ds;  \
                    const dtype ylo_val = ylo_tmp * TMPL_EPS(ylo_tmp);         \
                    const ddtype y = TMPL_DD_CREATE(yhi_val, ylo_val);         \
                    const long double yhi_ld = TMPL_CAST(y.dat[0],long double);\
                    const long double ylo_ld = TMPL_CAST(y.dat[1],long double);\
                    const ddtype out = func(&x, &y);                           \
                    const long double hi = TMPL_CAST(out.dat[0], long double); \
                    const long double lo = TMPL_CAST(out.dat[1], long double); \
                    tmpl_tests_mpf_set_ld(yhi_mp, yhi_ld);                     \
                    tmpl_tests_mpf_set_ld(ylo_mp, ylo_ld);                     \
                    mpf_add(y_mp, yhi_mp, ylo_mp);                             \
                    tmpl_tests_mpf_set_ld(out_hi_mp, hi);                      \
                    tmpl_tests_mpf_set_ld(out_lo_mp, lo);                      \
                    mpf_add(out_mp, out_hi_mp, out_lo_mp);                     \
                    mpf_op(exact_mp, x_mp, y_mp);                              \
                    mpf_sub(err_mp, out_mp, exact_mp);                         \
                    if (mpf_sgn(exact_mp) != 0)                                \
                        mpf_div(err_mp, err_mp, exact_mp);                     \
                    err = tmpl_tests_mpf_get_ld(err_mp);                       \
                    if (TMPL_ABS(err) > eps_squared)                           \
                    {                                                          \
                        long double xhi_bad = TMPL_CAST(x.dat[0], long double);\
                        long double xlo_bad = TMPL_CAST(x.dat[1], long double);\
                        long double yhi_bad = TMPL_CAST(y.dat[0], long double);\
                        long double ylo_bad = TMPL_CAST(y.dat[1], long double);\
                        long double eval = tmpl_tests_mpf_get_ld(exact_mp);    \
                        puts("FAIL");                                          \
                        printf("    Input x hi = %+.50LE\n", xhi_bad);         \
                        printf("    Input x lo = %+.50LE\n", xlo_bad);         \
                        printf("    Input y hi = %+.50LE\n", yhi_bad);         \
                        printf("    Input y lo = %+.50LE\n", ylo_bad);         \
                        printf("    libtmpl hi = %+.50LE\n", hi);              \
                        printf("    libtmpl lo = %+.50LE\n", lo);              \
                        printf("    Exact      = %+.50LE\n", eval);            \
                        printf("    Error      = %+.50LE\n", err);             \
                        return -1;                                             \
                    }                                                          \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif

#endif
