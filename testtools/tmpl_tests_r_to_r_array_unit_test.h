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
#ifndef TMPL_TESTS_R_TO_R_ARRAY_UNIT_TEST_H
#define TMPL_TESTS_R_TO_R_ARRAY_UNIT_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/helper/tmpl_array_size.h>
#include <libtmpl/include/helper/tmpl_error_value.h>
#include <libtmpl/include/generic/tmpl_eps.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include <stddef.h>
#include <stdio.h>

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_R_TO_R_ARRAY_UNIT_TEST                                           *
 *  Purpose:                                                                  *
 *      Test functions of the form f: R -> R over a given array.              *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The data type (float, double, int, etc.).                         *
 *      func:                                                                 *
 *          The libtmpl function being tested.                                *
 *      indata:                                                               *
 *          The input array.                                                  *
 *      outdata:                                                              *
 *          The output array. To pass we need |func(indata) - outdata| small. *
 ******************************************************************************/
#define TMPL_R_TO_R_ARRAY_UNIT_TEST(type, func, indata, outdata)               \
int main(void)                                                                 \
{                                                                              \
    const type in[] = indata;                                                  \
    const type out[] = outdata;                                                \
    const type eps = 2 * TMPL_EPS(in[0]);                                      \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in);                      \
    size_t n;                                                                  \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type output = func(in[n]);                                       \
        const type err = TMPL_ERROR_VALUE(output, out[n]);                     \
        const tmpl_Bool val_is_nan = TMPL_IS_NAN(output);                      \
        const tmpl_Bool out_is_nan = TMPL_IS_NAN(out[n]);                      \
        if (out_is_nan && val_is_nan)                                          \
            continue;                                                          \
        else if ((val_is_nan != out_is_nan) || (err > eps))                    \
        {                                                                      \
            puts("FAIL");                                                      \
            printf("    Input   = %+.40LE\n", TMPL_CAST(in[n], long double));  \
            printf("    libtmpl = %+.40LE\n", TMPL_CAST(output, long double)); \
            printf("    Other   = %+.40LE\n", TMPL_CAST(out[n], long double)); \
            printf("    Error   = %+.40LE\n", TMPL_CAST(err, long double));    \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif
