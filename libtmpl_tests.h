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
#include <libtmpl/include/tmpl.h>
#include <libtmpl/include/tmpl_generic.h>
#include <libtmpl/include/tmpl_variadic.h>

#ifdef __cplusplus
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cfloat>
using namespace std;
#else
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>
#endif

#ifndef TMPL_NSAMPS
#ifdef _MSC_VER
#include <windows.h>
static inline size_t memsize(void)
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return TMPL_CAST(status.ullTotalPhys, size_t);
}
#else
#include <unistd.h>
static inline size_t memsize(void)
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return TMPL_CAST(pages * page_size, size_t);
}
#endif
#define NSAMPS(a) (4*memsize()/(5*sizeof(a)))
#else
#define NSAMPS(a) TMPL_CAST(TMPL_NSAMPS, size_t)
#endif

#define TMPL_RAND_REAL(type, val)                                              \
do {                                                                           \
    int my_temp_variable = rand();                                             \
    val = TMPL_CAST(my_temp_variable, type) / TMPL_CAST(RAND_MAX, type);       \
} while(0);

#define TMPL_OPEN_FILE(fp, name)                                               \
do {                                                                           \
    fp = fopen(name, "r");                                                     \
                                                                               \
    if (!fp)                                                                   \
    {                                                                          \
        puts("fopen failed. Aborting.");                                       \
        return -1;                                                             \
    }                                                                          \
                                                                               \
} while(0);

#define TMPL_STRING_TO_REAL(x, start, end) _Generic((x),                       \
    long double: strtold,                                                      \
    default:     strtod,                                                       \
    float:       strtof                                                        \
)(start, end)

/*  Helper macros to shorten up the tests. Undef first to avoid conflict.     */
#undef T
#undef F
#undef TINF
#undef TNAN
#undef DNUM
#undef BNUM
#undef EPS
#undef TINFF
#undef TNANF
#undef DNUMF
#undef BNUMF
#undef EPSF
#undef TINFL
#undef TNANL
#undef DNUML
#undef BNUML
#undef EPSL

#define T tmpl_True
#define F tmpl_False

#define TINF tmpl_Double_Infinity()
#define TINFF tmpl_Float_Infinity()
#define TINFL tmpl_LDouble_Infinity()

#define TNAN tmpl_Double_NaN()
#define TNANF tmpl_Float_NaN()
#define TNANL tmpl_LDouble_NaN()

#if TMPL_HAS_IEEE754_DOUBLE == 1
#define DNUM pow(2.0, 1 - (TMPL_DOUBLE_BIAS + TMPL_DOUBLE_MANTISSA_LENGTH))
#define BNUM pow(2.0, (TMPL_DOUBLE_BIAS))
#else
#define DNUM DBL_MIN
#define BNUM DBL_MAX
#endif

#if TMPL_HAS_IEEE754_FLOAT == 1
#define DNUMF powf(2.0F, 1 - (TMPL_FLOAT_BIAS + TMPL_FLOAT_MANTISSA_LENGTH))
#define BNUMF powf(2.0F, (TMPL_FLOAT_BIAS))
#else
#define DNUMF FLT_MIN
#define BNUMF FLT_MAX
#endif

#if TMPL_HAS_IEEE754_LDOUBLE == 1
#define DNUML powl(2.0L, 1 - (TMPL_LDOUBLE_BIAS + TMPL_LDOUBLE_MANTISSA_LENGTH))
#define BNUML powl(2.0L, (TMPL_LDOUBLE_BIAS))
#else
#define DNUML LDBL_MIN
#define BNUML LDBL_MAX
#endif

#define TMPL_TEST_REAL_FUNC_VS_REAL_FUNC_TIME_TEST(type, begin, finish, f0, f1)\
int main(void)                                                                 \
{                                                                              \
    long double max_abs = 0.0L;                                                \
    long double max_rel = 0.0L;                                                \
    long double rms_abs = 0.0L;                                                \
    long double rms_rel = 0.0L;                                                \
    long double temp;                                                          \
    type *x, *y0, *y1;                                                         \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    double libother_time, libtmpl_time, ratio;                                 \
                                                                               \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const size_t N = NSAMPS(type) / 3;                                         \
    const type dx = (end - start) / TMPL_CAST(N, type);                        \
    int success;                                                               \
                                                                               \
    TMPL_MALLOC_VARS(success, type, N, &x, &y0, &y1);                          \
                                                                               \
    if (!success)                                                              \
    {                                                                          \
        puts("malloc failed and returned NULL. Aborting.");                    \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1 "\n");                                              \
    printf("start:   %.16Le\n", TMPL_CAST(start, long double));                \
    printf("end:     %.16Le\n", TMPL_CAST(end, long double));                  \
    printf("samples: %zu\n", N);                                               \
    printf("dx:      %.16Le\n", TMPL_CAST(dx, long double));                   \
                                                                               \
    x[0] = start;                                                              \
    for (n = TMPL_CAST(1, size_t); n < N; ++n)                                 \
        x[n] = x[n-1] + dx;                                                    \
                                                                               \
    t1 = clock();                                                              \
    for (n = TMPL_CAST(0, size_t); n < N; ++n)                                 \
        y0[n] = f0(x[n]);                                                      \
    t2 = clock();                                                              \
    libtmpl_time = TMPL_CAST(t2 - t1, double) / CLOCKS_PER_SEC;                \
    printf("libtmpl: %f seconds\n", libtmpl_time);                             \
                                                                               \
    t1 = clock();                                                              \
    for (n = TMPL_CAST(0, size_t); n < N; ++n)                                 \
        y1[n] = f1(x[n]);                                                      \
    t2 = clock();                                                              \
    libother_time = TMPL_CAST(t2 - t1, double) / CLOCKS_PER_SEC;               \
    printf("C:       %f seconds\n", libother_time);                            \
                                                                               \
    for (n = TMPL_CAST(0, size_t); n < N; ++n)                                 \
    {                                                                          \
        temp = fabsl(TMPL_CAST(y0[n] - y1[n], long double));                   \
        rms_abs += temp*temp;                                                  \
        if (max_abs < temp)                                                    \
            max_abs = temp;                                                    \
                                                                               \
        temp = fabsl(TMPL_CAST((y0[n] - y1[n])/y1[n], long double));           \
                                                                               \
        if (y1[n] != 0)                                                        \
        {                                                                      \
            rms_rel += temp*temp;                                              \
                                                                               \
            if (max_rel < temp)                                                \
                max_rel = temp;                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    rms_rel = sqrtl(rms_rel / TMPL_CAST(N, long double));                      \
    rms_abs = sqrtl(rms_abs / TMPL_CAST(N, long double));                      \
    ratio = libtmpl_time / libother_time;                                      \
    printf("max abs error: %.16Le\n", max_abs);                                \
    printf("max rel error: %.16Le\n", max_rel);                                \
    printf("rms abs error: %.16Le\n", rms_abs);                                \
    printf("rms rel error: %.16Le\n", rms_rel);                                \
    if (ratio < 0.5)                                                           \
        printf("SPEED TEST: INSANELY FASTER");                                 \
    else if (ratio < 0.9)                                                      \
        printf("SPEED TEST: FASTER");                                          \
    else if (0.9 <= ratio && ratio <= 1.1)                                     \
        printf("SPEED TEST: ABOUT THE SAME");                                  \
    else if (ratio < 1.5)                                                      \
        printf("SPEED TEST: SLOWER");                                          \
    else                                                                       \
        printf("SPEED TEST: INSANELY SLOWER");                                 \
    printf(" (ratio = %.4F)\n", ratio);                                        \
    free(x);                                                                   \
    free(y0);                                                                  \
    free(y1);                                                                  \
    return 0;                                                                  \
}

#ifdef _OPENMP
#define TMPL_TEST_REAL_FUNC_VS_REAL_FUNC_UNIT_TEST(type, begin, finish, f0, f1)\
int main(void)                                                                 \
{                                                                              \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    size_t n;                                                                  \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const size_t number_of_samples = NSAMPS(type);                             \
    const type dx = (end - start) / TMPL_CAST(number_of_samples, type);        \
    const type eps = TMPL_CAST(4, type) * TMPL_EPS(dx);                        \
    volatile int flag = 0;                                                     \
    volatile type error = TMPL_CAST(0, type);                                  \
    volatile type x_bad, y_bad, z_bad;                                         \
                                                                               \
    _Pragma("omp parallel for shared(flag, error)")                            \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        if (flag)                                                              \
            continue;                                                          \
        else                                                                   \
        {                                                                      \
            const type x = TMPL_CAST(n, type) * dx + start;                    \
            const type y = f0(x);                                              \
            const type z = f1(x);                                              \
            const type err = (y - z) / z;                                      \
            const type abs_err = (err > 0 ? err : -err);                       \
                                                                               \
            if (!TMPL_IS_NAN(err) && abs_err > eps)                            \
            {                                                                  \
                x_bad = x;                                                     \
                y_bad = y;                                                     \
                z_bad = z;                                                     \
                error = err;                                                   \
                flag = 1;                                                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    if (flag)                                                                  \
    {                                                                          \
            puts("FAIL");                                                      \
            printf("    Input   = %+.40LE\n", TMPL_CAST(x_bad, long double));  \
            printf("    libtmpl = %+.40LE\n", TMPL_CAST(y_bad, long double));  \
            printf("    Other   = %+.40LE\n", TMPL_CAST(z_bad, long double));  \
            printf("    Error   = %+.40LE\n", TMPL_CAST(error, long double));  \
    }                                                                          \
    else                                                                       \
        puts("PASS");                                                          \
    return 0;                                                                  \
}
#else
#define TMPL_TEST_REAL_FUNC_VS_REAL_FUNC_UNIT_TEST(type, begin, finish, f0, f1)\
int main(void)                                                                 \
{                                                                              \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    size_t n;                                                                  \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const size_t number_of_samples = NSAMPS(type);                             \
    const type dx = (end - start) / TMPL_CAST(number_of_samples, type);        \
    const type eps = (type)(4) * TMPL_EPS(dx);                                 \
                                                                               \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type x = ((type)n) * dx + start;                                 \
        const type y = f0(x);                                                  \
        const type z = f1(x);                                                  \
        const type err = (y - z) / z;                                          \
        const type error = (err > 0 ? err : -err);                             \
                                                                               \
        if (!TMPL_IS_NAN(err) && error > eps)                                  \
        {                                                                      \
            const long double x_bad = TMPL_CAST(x, long double);               \
            const long double y_bad = TMPL_CAST(y, long double);               \
            const long double z_bad = TMPL_CAST(z, long double);               \
            const long double error_bad = TMPL_CAST(error, long double);       \
            puts("FAIL");                                                      \
            printf("    Input   = %+.40LE\n", x_bad);                          \
            printf("    libtmpl = %+.40LE\n", y_bad);                          \
            printf("    Other   = %+.40LE\n", z_bad);                          \
            printf("    Error   = %+.40LE\n", error_bad);                      \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
    return 0;                                                                  \
}
#endif

#define TMPL_TEST_REAL_BOOL_VS_REAL_BOOL_UNIT_TEST(type, begin, finish, f0, f1)\
int main(void)                                                                 \
{                                                                              \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    size_t n;                                                                  \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const size_t number_of_samples = NSAMPS(type);                             \
    const type dx = (end - start) / TMPL_CAST(number_of_samples, type);        \
    type x = start;                                                            \
                                                                               \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const tmpl_Bool left = f0(x);                                          \
        const int right = f1(x);                                               \
                                                                               \
        if ((int)left != right)                                                \
        {                                                                      \
            puts("FAIL");                                                      \
            return -1;                                                         \
        }                                                                      \
                                                                               \
        x += dx;                                                               \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#define TMPL_TEST_REAL_FROM_CSV_UNIT_TEST(type, csv, f)                        \
int main(void)                                                                 \
{                                                                              \
    char buffer[1024];                                                         \
    char *line, *start, *end;                                                  \
    FILE *fp;                                                                  \
    type x, y, z, err, abs_err;                                                \
    const type eps = (type)(4) * TMPL_EPS(x);                                  \
                                                                               \
    TMPL_OPEN_FILE(fp, csv);                                                   \
                                                                               \
    line = fgets(buffer, sizeof(buffer), fp);                                  \
                                                                               \
    while (line)                                                               \
    {                                                                          \
        x = TMPL_STRING_TO_REAL(x, line, &start);                              \
        z = TMPL_STRING_TO_REAL(z, start + 1, &end);                           \
        y = f(x);                                                              \
        err = (y - z) / z;                                                     \
        abs_err = (err > 0 ? err : -err);                                      \
                                                                               \
        if (!TMPL_IS_NAN(err) && abs_err > eps)                                \
        {                                                                      \
            printf("FAIL: Max Error = %.8LE\n", (long double)abs_err);         \
            fclose(fp);                                                        \
            return -1;                                                         \
        }                                                                      \
                                                                               \
        line = fgets(buffer, sizeof(buffer), fp);                              \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
    fclose(fp);                                                                \
    return 0;                                                                  \
}

#define TMPL_REAL2_FUNC_VS_REAL2_FUNC_FROM_ARRAY(type, func0, func1, indata)   \
int main(void)                                                                 \
{                                                                              \
    typedef struct {type x, y;} arr2;                                          \
    const arr2 in[] = indata;                                                  \
    size_t n;                                                                  \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in);                      \
    const long double eps = TMPL_CAST(TMPL_EPS(in[0]), long double);           \
    long double err = 0.0L;                                                    \
                                                                               \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type x = in[n].x;                                                \
        const type y = in[n].y;                                                \
        const type z0 = func0(x, y);                                           \
        const type z1 = func0(x, y);                                           \
        const type err = (z1 - z0) / z1;                                       \
        const type error = (err > 0 ? err : -err);                             \
                                                                               \
        if (!TMPL_IS_NAN(err) && error > eps)                                  \
        {                                                                      \
            const long double x_bad = TMPL_CAST(x, long double);               \
            const long double y_bad = TMPL_CAST(y, long double);               \
            const long double z0_bad = TMPL_CAST(z0, long double);             \
            const long double z1_bad = TMPL_CAST(z1, long double);             \
            const long double error_bad = TMPL_CAST(error, long double);       \
            puts("FAIL");                                                      \
            printf("    Input   = (%+.40LE, %+.40LE)\n", x_bad, y_bad);        \
            printf("    libtmpl = %+.40LE\n", z0_bad);                         \
            printf("    Other   = %+.40LE\n", z1_bad);                         \
            printf("    Error   = %+.40LE\n", error_bad);                      \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
    return 0;                                                                  \
}
