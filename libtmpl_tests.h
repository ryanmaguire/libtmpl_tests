/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************/
#include <libtmpl/include/tmpl.h>

#ifdef __cplusplus
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
using namespace std;
#define TMPL_CAST(x, type) static_cast<type>((x))
#define TMPL_MALLOC(x, type, N) static_cast<type *>(malloc(sizeof(*x)*N))
#else
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define TMPL_CAST(x, type) (type)((x))
#define TMPL_MALLOC(x, type, N) malloc(sizeof(*x) * N)
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
    val = (type)my_temp_variable / (type)RAND_MAX;                             \
} while(0);

#define TMPL_FREE(var) if (var){free(var);}

#define TMPL_ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define TMPL_MALLOC_VARS(type, length, ...)                                    \
do {                                                                           \
    type **ptr_arr[] = {__VA_ARGS__};                                          \
    const size_t ptr_arr_len = TMPL_ARR_SIZE(ptr_arr);                         \
    size_t iterator;                                                           \
    for (iterator = 0; iterator < ptr_arr_len; ++iterator)                     \
    {                                                                          \
        *ptr_arr[iterator] = TMPL_MALLOC(ptr_arr[iterator], type, length);     \
    }                                                                          \
} while(0)

#define TMPL_EPS(x) _Generic((x),                                              \
    long double: TMPL_LDBL_EPS,                                                \
    default:     TMPL_DBL_EPS,                                                 \
    float:       TMPL_FLT_EPS                                                  \
)

#define TMPL_NULL_CHECKER(...)                                                 \
do {                                                                           \
    int should_free = 0;                                                       \
    void *ptr_arr[] = {__VA_ARGS__};                                           \
    const size_t ptr_arr_len = TMPL_ARR_SIZE(ptr_arr);                         \
    size_t iterator;                                                           \
    for (iterator = 0; iterator < ptr_arr_len; ++iterator)                     \
    {                                                                          \
        if (should_free)                                                       \
        {                                                                      \
            TMPL_FREE(ptr_arr[iterator])                                       \
        }                                                                      \
        else if (ptr_arr[iterator] == NULL)                                    \
        {                                                                      \
            should_free = 1;                                                   \
        }                                                                      \
    }                                                                          \
    if (should_free)                                                           \
    {                                                                          \
        puts("One of the pointers is NULL. Aborting.");                        \
        return -1;                                                             \
    }                                                                          \
} while(0)

#define TMPL_IS_NAN(x) _Generic((x),                                           \
    long double: tmpl_LDouble_Is_NaN,                                          \
    default:     tmpl_Double_Is_NaN,                                           \
    float:       tmpl_Float_Is_NaN                                             \
)(x)

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

#define TMPL_STRING_TO_REAL(x, start, end)  _Generic((x),                      \
    long double: strtold,                                                      \
    default:     strtod,                                                       \
    float:       strtof                                                        \
)(start, end)

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
                                                                               \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const size_t N = NSAMPS(type) / 3;                                         \
    const type dx = (end - start) / TMPL_CAST(N, type);                        \
                                                                               \
    TMPL_MALLOC_VARS(type, N, &x, &y0, &y1);                                   \
    TMPL_NULL_CHECKER(x, y0, y1);                                              \
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
    printf("libtmpl: %f seconds\n", TMPL_CAST(t2-t1, double)/CLOCKS_PER_SEC);  \
                                                                               \
    t1 = clock();                                                              \
    for (n = TMPL_CAST(0, size_t); n < N; ++n)                                 \
        y1[n] = f1(x[n]);                                                      \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", TMPL_CAST(t2-t1, double)/CLOCKS_PER_SEC);  \
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
    printf("max abs error: %.16Le\n", max_abs);                                \
    printf("max rel error: %.16Le\n", max_rel);                                \
    printf("rms abs error: %.16Le\n", rms_abs);                                \
    printf("rms rel error: %.16Le\n", rms_rel);                                \
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
                error = err;                                                   \
                flag = 1;                                                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    if (flag)                                                                  \
        printf("FAIL: Max Error = %.8LE\n", TMPL_CAST(error, long double));    \
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
        const type abs_err = (err > 0 ? err : -err);                           \
                                                                               \
        if (!TMPL_IS_NAN(err) && abs_err > eps)                                \
        {                                                                      \
            printf("FAIL: Max Error = %.8LE\n", (long double)abs_err);         \
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
