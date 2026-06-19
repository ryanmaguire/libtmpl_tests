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
#ifndef TMPL_TESTS_THREEVEC2_TO_R_VS_XYZ_TIME_TESTS_H
#define TMPL_TESTS_THREEVEC2_TO_R_VS_XYZ_TIME_TESTS_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/tmpl_variadic.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tmpl_tests_memsize.h"
#include "tmpl_tests_rand_real.h"

#define TMPL_THREEVEC2_TO_R_VS_XYZ_TIME_TESTS(ctype, ttype, ltype, f0, f1)     \
int main(void)                                                                 \
{                                                                              \
    ltype *A, *B;                                                              \
    ttype *X, *Y;                                                              \
    ctype *C, *Z;                                                              \
    const size_t number_of_samples = NSAMPS2(ttype, ltype) / 6;                \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max = 0.0L;                                                    \
    long double rms = 0.0L;                                                    \
    long double tmp = 0.0L;                                                    \
    double libtmpl_time, other_time;                                           \
    int success = 0;                                                           \
    TMPL_MALLOC_VARS(success, ltype, number_of_samples, &A, &B);               \
    TMPL_MALLOC_VARS(success, ttype, number_of_samples, &X, &Y);               \
    TMPL_MALLOC_VARS(success, ctype, number_of_samples, &C, &Z);               \
    if (!success)                                                              \
    {                                                                          \
        TMPL_FREE_VARS(ltype, &A, &B);                                         \
        TMPL_FREE_VARS(ttype, &X, &Y);                                         \
        TMPL_FREE_VARS(ctype, &C, &Z);                                         \
        puts("malloc failed and returned NULL. Aborting.");                    \
        return -1;                                                             \
    }                                                                          \
    for (n = 0U; n < number_of_samples; ++n)                                   \
    {                                                                          \
        ctype u0, u1, u2, v0, v1, v2;                                          \
        TMPL_RAND_REAL(ctype, u0);                                             \
        TMPL_RAND_REAL(ctype, u1);                                             \
        TMPL_RAND_REAL(ctype, u2);                                             \
        TMPL_RAND_REAL(ctype, v0);                                             \
        TMPL_RAND_REAL(ctype, v1);                                             \
        TMPL_RAND_REAL(ctype, v2);                                             \
                                                                               \
        X[n].dat[0] = u0;                                                      \
        X[n].dat[1] = u1;                                                      \
        X[n].dat[2] = u2;                                                      \
                                                                               \
        Y[n].dat[0] = v0;                                                      \
        Y[n].dat[1] = v1;                                                      \
        Y[n].dat[2] = v2;                                                      \
                                                                               \
        A[n].x = u0;                                                           \
        A[n].y = u1;                                                           \
        A[n].z = u2;                                                           \
                                                                               \
        B[n].x = v0;                                                           \
        B[n].y = v1;                                                           \
        B[n].z = v2;                                                           \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1"\n");                                               \
    printf("samples: %zu\n", number_of_samples);                               \
    t1 = clock();                                                              \
    for (n = 0U; n < number_of_samples; ++n)                                   \
        Z[n] = f0(&X[n], &Y[n]);                                               \
    t2 = clock();                                                              \
    libtmpl_time = TMPL_CAST(t2 - t1, double) / CLOCKS_PER_SEC;                \
    printf("libtmpl: %f seconds\n",  libtmpl_time);                            \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < number_of_samples; ++n)                                   \
        C[n] = f1(&A[n], &B[n]);                                               \
    t2 = clock();                                                              \
    other_time = TMPL_CAST(t2 - t1, double) / CLOCKS_PER_SEC;                  \
    printf("other:   %f seconds\n",  other_time);                              \
                                                                               \
    for (n = 0U; n < number_of_samples; ++n)                                   \
    {                                                                          \
        tmp = fabsl(TMPL_CAST(Z[n] - C[n], long double));                      \
        rms += tmp * tmp;                                                      \
                                                                               \
        if (max < tmp)                                                         \
            max = tmp;                                                         \
    }                                                                          \
                                                                               \
    rms = sqrtl(rms / TMPL_CAST(number_of_samples, long double));              \
                                                                               \
    printf("max err: %Le\n", max);                                             \
    printf("rms err: %Le\n", rms);                                             \
    TMPL_FREE_VARS(ltype, &A, &B);                                             \
    TMPL_FREE_VARS(ttype, &X, &Y);                                             \
    TMPL_FREE_VARS(ctype, &C, &Z);                                             \
    return 0;                                                                  \
}

#endif
