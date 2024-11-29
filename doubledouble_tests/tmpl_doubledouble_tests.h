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
#include <libtmpl/include/tmpl_doubledouble.h>
#include "../libtmpl_tests.h"

#ifndef TMPL_NO_QUADMATH
#include <quadmath.h>
#define TMPL_QUAD_FORMAT_STRING "%.40QE"
#else
typedef long double __float128;
#define quadmath_snprintf snprintf
#define fabsq fabsl
#define TMPL_QUAD_FORMAT_STRING "%.40LE"
#endif
#define TMPL_QUAD_EPS (1.9259299443872358530559779425849273185381E-34L)

static void quad_print(__float128 val)
{
    char buffer[1024];
    quadmath_snprintf(buffer, sizeof(buffer), TMPL_QUAD_FORMAT_STRING, val);
    printf("%s\n", buffer);
}

static inline __float128 dd_to_flt128(tmpl_DoubleDouble z)
{
    const __float128 hi = TMPL_CAST(z.dat[0], __float128);
    const __float128 lo = TMPL_CAST(z.dat[1], __float128);
    return hi + lo;
}

static inline __float128 ldd_to_flt128(tmpl_LongDoubleDouble z)
{
    const __float128 hi = TMPL_CAST(z.dat[0], __float128);
    const __float128 lo = TMPL_CAST(z.dat[1], __float128);
    return hi + lo;
}

static inline long double dd_to_ld(tmpl_DoubleDouble z)
{
    const long double hi = TMPL_CAST(z.dat[0], long double);
    const long double lo = TMPL_CAST(z.dat[1], long double);
    return hi + lo;
}

static inline long double ldd_to_ld(tmpl_LongDoubleDouble z)
{
    return z.dat[0] + z.dat[1];
}

static inline tmpl_DoubleDouble ld_to_dd(long double z)
{
    const double hi = TMPL_CAST(z, double);
    const long double hi_ldouble = TMPL_CAST(hi, long double);
    const long double lo_ldouble = z - hi_ldouble;
    const double lo = TMPL_CAST(lo_ldouble, double);
    return tmpl_DoubleDouble_Create(hi, lo);
}

static inline tmpl_LongDoubleDouble ld_to_ldd(long double z)
{
    tmpl_LongDoubleDouble out;
    out.dat[0] = z;
    out.dat[1] = 0.0L;
    return out;
}

static inline void
generate_flt128(tmpl_DoubleDouble * restrict const x0,
                tmpl_DoubleDouble * restrict const y0,
                __float128 * restrict const x1,
                __float128 * restrict const y1)
{
    double r0, r1, r2, r3;
    const double scale = TMPL_CAST(TMPL_QUAD_EPS, double) / TMPL_DBL_EPS;

    TMPL_RAND_REAL(double, r0);
    TMPL_RAND_REAL(double, r1);
    TMPL_RAND_REAL(double, r2);
    TMPL_RAND_REAL(double, r3);

    r0 = 64.0 * (r0 - 0.5);
    r1 = 64.0 * (r1 - 0.5) * scale;
    r2 = 64.0 * (r2 - 0.5);
    r3 = 64.0 * (r3 - 0.5) * scale;

    *x0 = tmpl_DoubleDouble_Create(r0, r1);
    *y0 = tmpl_DoubleDouble_Create(r2, r3);
    *x1 = dd_to_flt128(*x0);
    *y1 = dd_to_flt128(*y0);
}

static inline void
generate_flt128l(tmpl_LongDoubleDouble * restrict const x0,
                 tmpl_LongDoubleDouble * restrict const y0,
                 __float128 * restrict const x1,
                 __float128 * restrict const y1)
{
    long double r0, r1, r2, r3;
    const long double scale = TMPL_QUAD_EPS / TMPL_LDBL_EPS;

    TMPL_RAND_REAL(long double, r0);
    TMPL_RAND_REAL(long double, r1);
    TMPL_RAND_REAL(long double, r2);
    TMPL_RAND_REAL(long double, r3);

    r0 = 64.0L * (r0 - 0.5L);
    r1 = 64.0L * (r1 - 0.5L) * scale;
    r2 = 64.0L * (r2 - 0.5L);
    r3 = 64.0L * (r3 - 0.5L) * scale;

    *x0 = tmpl_LDoubleDouble_Create(r0, r1);
    *y0 = tmpl_LDoubleDouble_Create(r2, r3);
    *x1 = ldd_to_flt128(*x0);
    *y1 = ldd_to_flt128(*y0);
}

static inline void
generate_ld(tmpl_DoubleDouble * restrict const x0,
            tmpl_DoubleDouble * restrict const y0,
            long double * restrict const x1,
            long double * restrict const y1)
{
    long double r0, r1;

    TMPL_RAND_REAL(long double, r0);
    TMPL_RAND_REAL(long double, r1);

    *x1 = r0;
    *y1 = r1;
    *x0 = ld_to_dd(*x1);
    *y0 = ld_to_dd(*y1);
}

static inline void
generate_ldl(tmpl_LongDoubleDouble * restrict const x0,
             tmpl_LongDoubleDouble * restrict const y0,
             long double * restrict const x1,
             long double * restrict const y1)
{
    long double r0, r1;

    TMPL_RAND_REAL(long double, r0);
    TMPL_RAND_REAL(long double, r1);

    *x1 = r0;
    *y1 = r1;
    *x0 = ld_to_ldd(*x1);
    *y0 = ld_to_ldd(*y1);
}

static inline tmpl_Bool compare_flt128(tmpl_DoubleDouble z0, __float128 z1)
{
    __float128 val = dd_to_flt128(z0);
    __float128 err = fabsq((val - z1) / z1);
    const double dbl_eps = TMPL_DBL_EPS;
    __float128 sqrt_eps = TMPL_CAST(dbl_eps, __float128);
    __float128 eps = sqrt_eps * sqrt_eps * TMPL_CAST(4, __float128);

    if (err > eps)
        return tmpl_False;

    return tmpl_True;
}

static inline tmpl_Bool compare_flt128l(tmpl_LongDoubleDouble z0, __float128 z1)
{
    __float128 val = ldd_to_flt128(z0);
    __float128 err = fabsq((val - z1) / z1);
    const long double ldbl_eps = TMPL_LDBL_EPS;
    __float128 sqrt_eps = TMPL_CAST(ldbl_eps, __float128);
    __float128 eps = sqrt_eps * sqrt_eps * TMPL_CAST(4, __float128);

    if (err > eps)
        return tmpl_False;

    return tmpl_True;
}

static inline tmpl_Bool compare_ld(tmpl_DoubleDouble z0, long double z1)
{
    long double val = dd_to_ld(z0);
    long double err = fabsl((val - z1) / z1);
    const long double eps = 4.0L * TMPL_LDBL_EPS;

    if (err > eps)
        return tmpl_False;

    return tmpl_True;
}

static inline tmpl_Bool compare_ldl(tmpl_LongDoubleDouble z0, long double z1)
{
    long double val = ldd_to_ld(z0);
    long double err = fabsl((val - z1) / z1);
    const long double eps = 4.0L * TMPL_LDBL_EPS;

    if (err > eps)
        return tmpl_False;

    return tmpl_True;
}

static inline void
fail_flt128(tmpl_DoubleDouble x0,
            tmpl_DoubleDouble y0,
            tmpl_DoubleDouble z0,
            __float128 z1)
{
    __float128 x128 = dd_to_flt128(x0);
    __float128 y128 = dd_to_flt128(y0);
    __float128 z128 = dd_to_flt128(z0);
    __float128 err = fabsq((z128 - z1) / z1);

    puts("FAIL");
    quad_print(x128);
    quad_print(y128);
    quad_print(z128);
    quad_print(z1);
    quad_print(err);
}

static inline void
fail_flt128l(tmpl_LongDoubleDouble x0,
             tmpl_LongDoubleDouble y0,
             tmpl_LongDoubleDouble z0,
             __float128 z1)
{
    __float128 x128 = ldd_to_flt128(x0);
    __float128 y128 = ldd_to_flt128(y0);
    __float128 z128 = ldd_to_flt128(z0);
    __float128 err = fabsq((z128 - z1) / z1);

    puts("FAIL");
    quad_print(x128);
    quad_print(y128);
    quad_print(z128);
    quad_print(z1);
    quad_print(err);
}

static inline void
fail_ld(tmpl_DoubleDouble x0,
        tmpl_DoubleDouble y0,
        tmpl_DoubleDouble z0,
        long double z1)
{
    const long double xld = dd_to_ld(x0);
    const long double yld = dd_to_ld(y0);
    const long double zld = dd_to_ld(z0);
    const long double err = fabsl((zld - z1) / z1);

    puts("FAIL");
    printf("    Input x = %+.40LE\n", xld);
    printf("    Input z = %+.40LE\n", yld);
    printf("    libtmpl = %+.40LE\n", zld);
    printf("    Other   = %+.40LE\n", z1);
    printf("    Error   = %+.40LE\n", err);
}

static inline void
fail_ldl(tmpl_LongDoubleDouble x0,
         tmpl_LongDoubleDouble y0,
         tmpl_LongDoubleDouble z0,
         long double z1)
{
    const long double xld = ldd_to_ld(x0);
    const long double yld = ldd_to_ld(y0);
    const long double zld = ldd_to_ld(z0);
    const long double err = fabsl((zld - z1) / z1);

    puts("FAIL");
    printf("    Input x = %+.40LE\n", xld);
    printf("    Input z = %+.40LE\n", yld);
    printf("    libtmpl = %+.40LE\n", zld);
    printf("    Other   = %+.40LE\n", z1);
    printf("    Error   = %+.40LE\n", err);
}

static inline void
get_flt128_error(const tmpl_DoubleDouble * restrict const z0,
                 const __float128 * restrict const z1,
                 size_t number_of_samples,
                 long double * restrict const rms_err,
                 long double * restrict const max_err)
{
    size_t n;
    *rms_err = 0.0L;
    *max_err = 0.0L;

    for (n = 0; n < number_of_samples; ++n)
    {
        __float128 val = dd_to_flt128(z0[n]);
        __float128 errQ = fabsq((val - z1[n]) / z1[n]);
        long double err = TMPL_CAST(errQ, long double);
        *rms_err += err*err;

        if (err > *max_err)
            *max_err = err;
    }

    *rms_err = *rms_err / TMPL_CAST(number_of_samples, long double);
}

static inline void
get_flt128l_error(const tmpl_LongDoubleDouble * restrict const z0,
                  const __float128 * restrict const z1,
                  size_t number_of_samples,
                  long double * restrict const rms_err,
                  long double * restrict const max_err)
{
    size_t n;
    *rms_err = 0.0L;
    *max_err = 0.0L;

    for (n = 0; n < number_of_samples; ++n)
    {
        __float128 val = ldd_to_flt128(z0[n]);
        __float128 errQ = fabsq((val - z1[n]) / z1[n]);
        long double err = TMPL_CAST(errQ, long double);
        *rms_err += err*err;

        if (err > *max_err)
            *max_err = err;
    }

    *rms_err = *rms_err / TMPL_CAST(number_of_samples, long double);
}

static inline void
get_ld_error(const tmpl_DoubleDouble * restrict const z0,
             const long double * restrict const z1,
             size_t number_of_samples,
             long double * restrict const rms_err,
             long double * restrict const max_err)
{
    size_t n;
    *rms_err = 0.0L;
    *max_err = 0.0L;

    for (n = 0; n < number_of_samples; ++n)
    {
        long double val = dd_to_ld(z0[n]);
        long double err = fabsl((val - z1[n]) / z1[n]);
        *rms_err += err*err;

        if (err > *max_err)
            *max_err = err;
    }

    *rms_err = *rms_err / TMPL_CAST(number_of_samples, long double);
}

static inline void
get_ldl_error(const tmpl_LongDoubleDouble * restrict const z0,
              const long double * restrict const z1,
              size_t number_of_samples,
              long double * restrict const rms_err,
              long double * restrict const max_err)
{
    size_t n;
    *rms_err = 0.0L;
    *max_err = 0.0L;

    for (n = 0; n < number_of_samples; ++n)
    {
        long double val = ldd_to_ld(z0[n]);
        long double err = fabsl((val - z1[n]) / z1[n]);
        *rms_err += err*err;

        if (err > *max_err)
            *max_err = err;
    }

    *rms_err = *rms_err / TMPL_CAST(number_of_samples, long double);
}
