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
#ifndef TMPL_TESTS_INT_ARRAY_IN_SIZE_T_OUT_UNIT_TEST_H
#define TMPL_TESTS_INT_ARRAY_IN_SIZE_T_OUT_UNIT_TEST_H
#include <libtmpl/include/helper/tmpl_array_size.h>

#define TMPL_INT_ARRAY_IN_SIZE_T_OUT_UNIT_TEST(type, func, arr, ans)           \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = TMPL_ARRAY_SIZE(in);                                    \
    const size_t out = func(in, len);                                          \
    if (out != ans)                                                            \
        puts("FAIL");                                                          \
    else                                                                       \
        puts("PASS");                                                          \
    return 0;                                                                  \
}

#endif
