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
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cfloat>
using namespace std;
#else
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
#define DNUM (+5.00000000000000E-324)
#define BNUM (+1.79769313486231E+308)
#else
#define DNUM DBL_MIN
#define BNUM DBL_MAX
#endif

#if TMPL_HAS_IEEE754_FLOAT == 1
#define DNUMF (+1.401298464324817E-45F)
#define BNUMF (+3.402823500000000E+38F)
#else
#define DNUMF FLT_MIN
#define BNUMF FLT_MAX
#endif

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT
#define DNUML (+5.00000000000000E-324L)
#define BNUML (+1.79769313486231E+308L)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
#define DNUML (+4.9406564584124654417656879286822137236505980261E-324L)
#define BNUML (+1.7976931348623100000000000000000000000000000000E+308L)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT
#define DNUML (+6.475175119438025110924438958227646552499569338E-4966L)
#define BNUML (+1.189731495357231765085759326628007130763444687E+4932L)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT
#define DNUML (+3.645199531882474602E-4951L)
#define BNUML (+1.189731495357231765E+4932L)
#else
#define DNUML LDBL_MIN
#define BNUML LDBL_MAX
#endif

#ifdef _OPENMP
#define TMPL_OPENMP_BASE_PRAGMA _Pragma("omp parallel for shared(flag, error)")
#define TMPL_OPENMP_BOOL_PRAGMA _Pragma("omp parallel for shared(flag)")
#else
#define TMPL_OPENMP_BASE_PRAGMA
#define TMPL_OPENMP_BOOL_PRAGMA
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
    TMPL_FREE(x);                                                              \
    TMPL_FREE(y0);                                                             \
    TMPL_FREE(y1);                                                             \
    return 0;                                                                  \
}

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
    const type real_zero = TMPL_CAST(0, type);                                 \
    volatile int flag = 0;                                                     \
    volatile type error = real_zero;                                           \
    volatile type x_bad = real_zero;                                           \
    volatile type y_bad = real_zero;                                           \
    volatile type z_bad = real_zero;                                           \
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
            const type err = (z == real_zero ? (y - z) : (y - z) / z);         \
            const type abs_err = TMPL_ABS(err);                                \
            if ((y_is_nan != z_is_nan) || (abs_err > eps))                     \
            {                                                                  \
                x_bad = x;                                                     \
                y_bad = y;                                                     \
                z_bad = z;                                                     \
                error = err;                                                   \
                flag = 1;                                                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
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

#define TMPL_TEST_REAL_BOOL_VS_REAL_BOOL_UNIT_TEST(type, begin, finish, f0, f1)\
int main(void)                                                                 \
{                                                                              \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    size_t n;                                                                  \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const size_t number_of_samples = NSAMPS(type);                             \
    const type dx = (end - start) / TMPL_CAST(number_of_samples, type);        \
    volatile int flag = 0;                                                     \
    volatile type x_bad = TMPL_CAST(0, type);                                  \
    volatile int y_bad = 0;                                                    \
    volatile int z_bad = 0;                                                    \
    TMPL_OPENMP_BOOL_PRAGMA                                                    \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        if (flag)                                                              \
            continue;                                                          \
        else                                                                   \
        {                                                                      \
            const type x = TMPL_CAST(n, type) * dx + start;                    \
            const tmpl_Bool y_tmp = f0(x);                                     \
            const int y = TMPL_CAST(y_tmp, int);                               \
            const int z = f1(x);                                               \
            if (y != z)                                                        \
            {                                                                  \
                x_bad = x;                                                     \
                y_bad = y;                                                     \
                z_bad = z;                                                     \
                flag = 1;                                                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    if (flag)                                                                  \
    {                                                                          \
            puts("FAIL");                                                      \
            printf("    Input   = %+.40LE\n", TMPL_CAST(x_bad, long double));  \
            printf("    libtmpl = %d\n", y_bad);                               \
            printf("    Other   = %d\n", z_bad);                               \
    }                                                                          \
    else                                                                       \
        puts("PASS");                                                          \
    return 0;                                                                  \
}

#define TMPL_TEST_REAL_FROM_CSV_UNIT_TEST(type, csv, f)                        \
int main(void)                                                                 \
{                                                                              \
    char buffer[1024];                                                         \
    char *line, *start, *end;                                                  \
    FILE *fp;                                                                  \
    type x, y, z, err, abs_err;                                                \
    const type eps = TMPL_CAST(4, type) * TMPL_EPS(x);                         \
    const type real_zero = TMPL_CAST(0, type);                                 \
    TMPL_OPEN_FILE(fp, csv);                                                   \
    line = fgets(buffer, sizeof(buffer), fp);                                  \
    while (line)                                                               \
    {                                                                          \
        x = TMPL_STRING_TO_REAL(x, line, &start);                              \
        z = TMPL_STRING_TO_REAL(z, start + 1, &end);                           \
        y = f(x);                                                              \
        err = (z == real_zero ? (y - z) : (y - z) / z);                        \
        abs_err = TMPL_ABS(err);                                               \
        if (!TMPL_IS_NAN(err) && abs_err > eps)                                \
        {                                                                      \
            puts("FAIL");                                                      \
            printf("    Input   = %+.40LE\n", TMPL_CAST(x, long double));      \
            printf("    libtmpl = %+.40LE\n", TMPL_CAST(y, long double));      \
            printf("    Other   = %+.40LE\n", TMPL_CAST(z, long double));      \
            printf("    Error   = %+.40LE\n", TMPL_CAST(err, long double));    \
            fclose(fp);                                                        \
            return -1;                                                         \
        }                                                                      \
        line = fgets(buffer, sizeof(buffer), fp);                              \
    }                                                                          \
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
    const type real_zero = TMPL_CAST(0, type);                                 \
    const type eps = TMPL_CAST(4, type) * TMPL_EPS(real_zero);                 \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type x = in[n].x;                                                \
        const type y = in[n].y;                                                \
        const type z0 = func0(x, y);                                           \
        const type z1 = func1(x, y);                                           \
        const type err = (z1 == real_zero ? (z0 - z1) : (z0 - z1) / z1);       \
        const type abs_err = TMPL_ABS(err);                                    \
        const tmpl_Bool z0_is_nan = TMPL_IS_NAN(z0);                           \
        const tmpl_Bool z1_is_nan = TMPL_IS_NAN(z1);                           \
        if ((z0_is_nan != z1_is_nan) || (abs_err > eps))                       \
        {                                                                      \
            const long double x_bad = TMPL_CAST(x, long double);               \
            const long double y_bad = TMPL_CAST(y, long double);               \
            const long double z0_bad = TMPL_CAST(z0, long double);             \
            const long double z1_bad = TMPL_CAST(z1, long double);             \
            const long double error = TMPL_CAST(abs_err, long double);         \
            puts("FAIL");                                                      \
            printf("    Input   = (%+.40LE, %+.40LE)\n", x_bad, y_bad);        \
            printf("    libtmpl = %+.40LE\n", z0_bad);                         \
            printf("    Other   = %+.40LE\n", z1_bad);                         \
            printf("    Error   = %+.40LE\n", error);                          \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}
