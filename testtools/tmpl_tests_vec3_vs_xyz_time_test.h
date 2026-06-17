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
#ifndef TMPL_TESTS_VEC3_VS_XYZ_TIME_TESTS_H
#define TMPL_TESTS_VEC3_VS_XYZ_TIME_TESTS_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/tmpl_variadic.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tmpl_tests_memsize.h"
#include "tmpl_tests_rand_real.h"

#define TMPL_VEC3_VS_XYZ_TIME_TESTS(ctype, ttype, ltype, f0, f1)               \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Y, *Z;                                                          \
    ltype *A, *B, *C;                                                          \
    const size_t number_of_samples = NSAMPS2(ttype, ltype) / 6;                \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double x_max = 0.0L;                                                  \
    long double y_max = 0.0L;                                                  \
    long double z_max = 0.0L;                                                  \
    long double x_rms = 0.0L;                                                  \
    long double y_rms = 0.0L;                                                  \
    long double z_rms = 0.0L;                                                  \
    long double tmp = 0.0L;                                                    \
    double libtmpl_time, other_time;                                           \
    int success = 0;                                                           \
    TMPL_MALLOC_VARS(success, ttype, number_of_samples, &X, &Y, &Z);           \
    TMPL_MALLOC_VARS(success, ltype, number_of_samples, &A, &B, &C);           \
    if (!success)                                                              \
    {                                                                          \
        TMPL_FREE_VARS(ttype, &X, &Y, &Z);                                     \
        TMPL_FREE_VARS(ltype, &A, &B, &C);                                     \
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
    {                                                                          \
        C[n] = A[n];                                                           \
        f1(&C[n], &B[n]);                                                      \
    }                                                                          \
    t2 = clock();                                                              \
    other_time = TMPL_CAST(t2 - t1, double) / CLOCKS_PER_SEC;                  \
    printf("other:   %f seconds\n",  other_time);                              \
                                                                               \
    for (n = 0U; n < number_of_samples; ++n)                                   \
    {                                                                          \
        tmp = fabsl(TMPL_CAST(Z[n].dat[0] - C[n].x, long double));             \
        x_rms += tmp * tmp;                                                    \
                                                                               \
        if (x_max < tmp)                                                       \
            x_max = tmp;                                                       \
                                                                               \
        tmp = fabsl(TMPL_CAST(Z[n].dat[1] - C[n].y, long double));             \
        y_rms += tmp * tmp;                                                    \
                                                                               \
        if (y_max < tmp)                                                       \
            y_max = tmp;                                                       \
                                                                               \
        tmp = fabsl(TMPL_CAST(Z[n].dat[2] - C[n].z, long double));             \
        z_rms += tmp * tmp;                                                    \
                                                                               \
        if (z_max < tmp)                                                       \
            z_max = tmp;                                                       \
    }                                                                          \
                                                                               \
    x_rms = sqrtl(x_rms / TMPL_CAST(number_of_samples, long double));          \
    y_rms = sqrtl(y_rms / TMPL_CAST(number_of_samples, long double));          \
    z_rms = sqrtl(z_rms / TMPL_CAST(number_of_samples, long double));          \
                                                                               \
    printf("x max err: %Le\n", x_max);                                         \
    printf("y max err: %Le\n", y_max);                                         \
    printf("z max err: %Le\n", z_max);                                         \
    printf("x rms err: %Le\n", x_rms);                                         \
    printf("y rms err: %Le\n", y_rms);                                         \
    printf("z rms err: %Le\n", z_rms);                                         \
                                                                               \
    TMPL_FREE_VARS(ttype, &X, &Y, &Z);                                         \
    TMPL_FREE_VARS(ltype, &A, &B, &C);                                         \
    return 0;                                                                  \
}

#endif
