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
#ifndef TMPL_TESTS_2DAT2_PTR_TO_R_ARRAY_EXACT_UNIT_TEST_H
#define TMPL_TESTS_2DAT2_PTR_TO_R_ARRAY_EXACT_UNIT_TEST_H

#define TMPL_2DAT2_PTR_TO_R_ARRAY_EXACT_UNIT_TEST(type, ftype, f, i0, i1, oarr)\
int main(void)                                                                 \
{                                                                              \
    const type in0[] = i0;                                                     \
    const type in1[] = i1;                                                     \
    const ftype out[] = oarr;                                                  \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in0);                     \
    size_t n;                                                                  \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const ftype output = f(&in0[n], &in1[n]);                              \
        const tmpl_Bool val_is_nan = TMPL_IS_NAN(output);                      \
        const tmpl_Bool out_is_nan = TMPL_IS_NAN(out[n]);                      \
        const tmpl_Bool val_equal = (output == out[n]);                        \
        const tmpl_Bool nan_pass = (val_is_nan && out_is_nan);                 \
        const tmpl_Bool nan_equal = (val_is_nan == out_is_nan);                \
        const tmpl_Bool val_pass = (nan_pass || (val_equal && nan_equal));     \
        if (!val_pass)                                                         \
        {                                                                      \
            const long double x0 = TMPL_CAST(in0[n].dat[0], long double);      \
            const long double y0 = TMPL_CAST(in0[n].dat[1], long double);      \
            const long double x1 = TMPL_CAST(in1[n].dat[0], long double);      \
            const long double y1 = TMPL_CAST(in1[n].dat[1], long double);      \
            const long double ol = TMPL_CAST(output, long double);             \
            const long double oc = TMPL_CAST(out[n], long double);             \
            const long double err = TMPL_ERROR_VALUE(ol, oc);                  \
            puts("FAIL");                                                      \
            printf("    Input x0 = %+.40LE\n", x0);                            \
            printf("    Input y0 = %+.40LE\n", y0);                            \
            printf("    Input x1 = %+.40LE\n", x1);                            \
            printf("    Input y1 = %+.40LE\n", y1);                            \
            printf("    libtmpl  = %+.40LE\n", ol);                            \
            printf("    Other    = %+.40LE\n", oc);                            \
            printf("    Error    = %+.40LE\n", err);                           \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif
