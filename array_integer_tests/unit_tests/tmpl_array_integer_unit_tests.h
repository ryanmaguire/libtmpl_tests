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
#ifndef TMPL_ARRAY_INTEGER_UNIT_TESTS_H
#define TMPL_ARRAY_INTEGER_UNIT_TESTS_H
#include <stdio.h>
#include <libtmpl/include/tmpl_array_integer.h>
#include <libtmpl/include/tmpl_float.h>

#define TMPL_EPS(x) _Generic((x), \
    float: TMPL_FLT_EPS,          \
    default: TMPL_DBL_EPS,        \
    long double: TMPL_LDBL_EPS    \
)

#define TEST_INT_ARRAY_IN_INT_TYPE_OUT(type, func, arr, ans)                   \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    const type out = func(in, len);                                            \
                                                                               \
    if (out != ans)                                                            \
        puts("FAIL");                                                          \
    else                                                                       \
        puts("PASS");                                                          \
                                                                               \
    return 0;                                                                  \
}

#define TEST_INT_ARRAY_IN_TWO_INT_TYPE_OUT(type, func, arr, ansa, ansb)        \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    type outa, outb;                                                           \
    func(in, len, &outa, &outb);                                               \
                                                                               \
    if ((outa != ansa) && (outb != ansb))                                      \
        puts("FAIL");                                                          \
    else                                                                       \
        puts("PASS");                                                          \
                                                                               \
    return 0;                                                                  \
}

#define TEST_INT_ARRAY_IN_SIZE_T_OUT(type, func, arr, ans)                     \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    const size_t out = func(in, len);                                          \
                                                                               \
    if (out != ans)                                                            \
        puts("FAIL");                                                          \
    else                                                                       \
        puts("PASS");                                                          \
                                                                               \
    return 0;                                                                  \
}

#define TEST_INT_ARRAY_IN_TWO_SIZE_T_OUT(type, func, arr, ansa, ansb)          \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    size_t outa, outb;                                                         \
    func(in, len, &outa, &outb);                                               \
                                                                               \
    if ((outa != ansa) && (outb != ansb))                                      \
        puts("FAIL");                                                          \
    else                                                                       \
        puts("PASS");                                                          \
                                                                               \
    return 0;                                                                  \
}

#define TEST_INT_ARRAY_IN_FLOAT_TYPE_OUT(type, ftype, func, arr, ans)          \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    const ftype out = func(in, len);                                           \
                                                                               \
    if (out != ans)                                                            \
        puts("FAIL");                                                          \
    else                                                                       \
        puts("PASS");                                                          \
                                                                               \
    return 0;                                                                  \
}

#define TEST_INT_ARRAY_IN_FLOAT_TYPE_OUT_WITH_ERR(type, ftype, func, arr, ans) \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    const ftype out = func(in, len);                                           \
    const ftype eps = ((ftype)4) * TMPL_EPS(out);                              \
    const ftype tmp = (out - ans) / ans;                                       \
    const ftype err = (tmp > 0 ? tmp : -tmp);                                  \
                                                                               \
    if (err > eps)                                                             \
        puts("FAIL");                                                          \
    else                                                                       \
        puts("PASS");                                                          \
                                                                               \
    return 0;                                                                  \
}

#endif
