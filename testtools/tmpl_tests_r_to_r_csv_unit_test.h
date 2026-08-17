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
#ifndef TMPL_TESTS_R_TO_R_CSV_UNIT_TEST_H
#define TMPL_TESTS_R_TO_R_CSV_UNIT_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/helper/tmpl_array_size.h>
#include <libtmpl/include/helper/tmpl_error_value.h>
#include <libtmpl/include/generic/tmpl_eps.h>
#include <libtmpl/include/generic/tmpl_is_nan.h>
#include <stddef.h>
#include <stdio.h>

#define TMPL_R_TO_R_CSV_UNIT_TEST(type, csv, f)                                \
int main(void)                                                                 \
{                                                                              \
    char buffer[1024];                                                         \
    char *line, *start, *end;                                                  \
    FILE *fp;                                                                  \
    const type real_zero = TMPL_CAST(0, type);                                 \
    const type eps = TMPL_DEFAULT_TOLERANCE * TMPL_EPS(real_zero);             \
    TMPL_OPEN_FILE(fp, csv);                                                   \
    line = fgets(buffer, sizeof(buffer), fp);                                  \
    (void)real_zero;                                                           \
    while (line)                                                               \
    {                                                                          \
        const type x = TMPL_STRING_TO_REAL(x, line, &start);                   \
        const type z = TMPL_STRING_TO_REAL(z, start + 1, &end);                \
        const type y = f(x);                                                   \
        const type err = TMPL_ERROR_VALUE(y, z);                               \
        const tmpl_Bool y_is_nan = TMPL_IS_NAN(y);                             \
        const tmpl_Bool z_is_nan = TMPL_IS_NAN(z);                             \
        if ((y_is_nan != z_is_nan) || (err > eps))                             \
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

#endif
