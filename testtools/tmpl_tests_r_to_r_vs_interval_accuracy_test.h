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
#ifndef TMPL_TESTS_R_TO_R_VS_INTERVAL_ACCURACY_TEST_H
#define TMPL_TESTS_R_TO_R_VS_INTERVAL_ACCURACY_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>

#define TMPL_R_TO_R_VS_INTERVAL_ACCURACY_TEST(type, begin, finish, len, f0, f1)\
int main(void)                                                                 \
{                                                                              \
    const size_t number_of_samples = TMPL_CAST(len, size_t);                   \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const type dx = (end - start) / TMPL_CAST(number_of_samples - 1, type);    \
    const type zero = TMPL_CAST(0, type);                                      \
    long double max_abs = 0.0L;                                                \
    long double max_rel = 0.0L;                                                \
    long double rms_rel = 0.0L;                                                \
    long double rms_abs = 0.0L;                                                \
    size_t n;                                                                  \
                                                                               \
    printf(#f0 " vs. " #f1 "\n");                                              \
    printf("start:   %+.8LE\n", TMPL_CAST(start, long double));                \
    printf("end:     %+.8LE\n", TMPL_CAST(end, long double));                  \
    printf("samples:  %zu\n", number_of_samples);                              \
    printf("dx:      %+.8LE\n", TMPL_CAST(dx, long double));                   \
                                                                               \
    for (n = 0; n < number_of_samples; ++n)                                    \
    {                                                                          \
        const type x = start + TMPL_CAST(n, type) * dx;                        \
        const type y0 = f0(x);                                                 \
        const type y1 = f1(x);                                                 \
        const long double y0_ld = TMPL_CAST(y0, long double);                  \
        const long double y1_ld = TMPL_CAST(y1, long double);                  \
        const long double diff = y0_ld - y1_ld;                                \
        const long double abs_diff = fabsl(diff);                              \
                                                                               \
        if ((x < start) || (x > end))                                          \
            break;                                                             \
                                                                               \
        rms_abs += abs_diff * abs_diff;                                        \
                                                                               \
        if (max_abs < abs_diff)                                                \
            max_abs = abs_diff;                                                \
                                                                               \
        if (y1 != zero)                                                        \
        {                                                                      \
            const long double rel_err = fabsl(diff / y1_ld);                   \
            rms_rel += rel_err * rel_err;                                      \
                                                                               \
            if (max_rel < rel_err)                                             \
                max_rel = rel_err;                                             \
        }                                                                      \
    }                                                                          \
                                                                               \
    rms_rel = sqrtl(rms_rel / TMPL_CAST(number_of_samples, long double));      \
    rms_abs = sqrtl(rms_abs / TMPL_CAST(number_of_samples, long double));      \
    printf("max rel error: %.8LE\n", max_rel);                                 \
    printf("rms rel error: %.8LE\n", rms_rel);                                 \
    printf("max abs error: %.8LE\n", max_abs);                                 \
    printf("rms abs error: %.8LE\n", rms_abs);                                 \
}

#endif
