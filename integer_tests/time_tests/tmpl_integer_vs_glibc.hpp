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
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <numeric>
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/tmpl_integer.h>

extern "C" {
#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
}

#ifndef TMPL_NSAMPS
#ifdef _MSC_VER
#include <windows.h>
static size_t memsize(void)
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return (size_t)(status.ullTotalPhys);
}
#else
#include <unistd.h>
static size_t memsize(void)
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return (size_t)(pages * page_size);
}
#endif
#define NSAMPS(a) (4*memsize()/(5*sizeof(a)))
#else
#define NSAMPS(a) TMPL_CAST(TMPL_NSAMPS, size_t)
#endif

static double time_as_double(clock_t a, clock_t b)
{
    double t = static_cast<double>(b - a);
    return t / static_cast<double>(CLOCKS_PER_SEC);
}

#define TEST1(type, f0, f1)                                                    \
                                                                               \
static type random_int(void)                                                   \
{                                                                              \
    int a = std::rand();                                                       \
                                                                               \
    while (a == 0)                                                             \
    {                                                                          \
        a = std::rand();                                                       \
    }                                                                          \
                                                                               \
    return static_cast<type>(a);                                               \
}                                                                              \
                                                                               \
int main(void)                                                                 \
{                                                                              \
    type *A, *B, *C, *Z;                                                       \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    const size_t N = NSAMPS(type) / 6;                                         \
    A = static_cast<type *>(std::malloc(sizeof(*A)*N));                        \
    if (!A)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for B. Aborting.");                           \
    	return -1;                                                             \
    }                                                                          \
    B = static_cast<type *>(std::malloc(sizeof(*B)*N));                        \
    if (!B)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for B. Aborting.");                           \
    	std::free(A);                                                          \
    	return -1;                                                             \
    }                                                                          \
    C = static_cast<type *>(std::malloc(sizeof(*C)*N));                        \
    if (!C)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for C. Aborting.");                           \
    	std::free(A);                                                          \
    	std::free(B);                                                          \
    	return -1;                                                             \
    }                                                                          \
    Z = static_cast<type *>(std::malloc(sizeof(*Z)*N));                        \
    if (!Z)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for Z. Aborting.");                           \
    	std::free(A);                                                          \
    	std::free(B);                                                          \
    	std::free(C);                                                          \
    	return -1;                                                             \
    }                                                                          \
                                                                               \
    std::printf(#f0 " vs. " #f1 "\n");                                         \
    std::printf("samples: %zu\n", N);                                          \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        A[n] = random_int();                                                   \
        B[n] = random_int();                                                   \
    }                                                                          \
                                                                               \
    t1 = std::clock();                                                         \
    for (n = 0; n < N; ++n)                                                    \
        C[n] = f0(A[n], B[n]);                                                 \
    t2 = std::clock();                                                         \
    printf("libtmpl: %f\n", time_as_double(t1, t2));                           \
                                                                               \
    t1 = std::clock();                                                         \
    for (n = 0; n < N; ++n)                                                    \
        Z[n] = f1(A[n], B[n]);                                                 \
    t2 = std::clock();                                                         \
    printf("cpp:     %f\n", time_as_double(t1, t2));                           \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        if (C[n] != Z[n])                                                      \
        {                                                                      \
            puts("FAIL");                                                      \
            printf("x       = %ld\n", TMPL_CAST(A[n], signed long int));       \
            printf("y       = %ld\n", TMPL_CAST(B[n], signed long int));       \
            printf("libtmpl = %ld\n", TMPL_CAST(C[n], signed long int));       \
            printf("other   = %ld\n", TMPL_CAST(Z[n], signed long int));       \
            break;                                                             \
        }                                                                      \
    }                                                                          \
    std::free(A);                                                              \
    std::free(B);                                                              \
    std::free(C);                                                              \
    std::free(Z);                                                              \
    return 0;                                                                  \
}
