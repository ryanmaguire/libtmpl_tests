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
#ifndef TMPL_TESTS_C_TO_R_ARRAY_EXACT_UNIT_TEST_H
#define TMPL_TESTS_C_TO_R_ARRAY_EXACT_UNIT_TEST_H

#define TMPL_C_TO_R_ARRAY_EXACT_UNIT_TEST(type, ftype, func, inarr, outarr)    \
int main(void)                                                                 \
{                                                                              \
    const type in[] = inarr;                                                   \
    const ftype out[] = outarr;                                                \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in);                      \
    size_t n;                                                                  \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const ftype output = func(in[n]);                                      \
        const tmpl_Bool val_is_nan = TMPL_IS_NAN(output);                      \
        const tmpl_Bool out_is_nan = TMPL_IS_NAN(out[n]);                      \
        if (out_is_nan && val_is_nan)                                          \
            continue;                                                          \
        if ((val_is_nan != out_is_nan) || (output != out[n]))                  \
        {                                                                      \
            const ftype err = TMPL_ERROR_VALUE(output, out[n]);                \
            const long double x_val = TMPL_CAST(in[n].dat[0], long double);    \
            const long double y_val = TMPL_CAST(in[n].dat[1], long double);    \
            puts("FAIL");                                                      \
            printf("    Input x = %+.40LE\n", x_val);                          \
            printf("    Input y = %+.40LE\n", y_val);                          \
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
