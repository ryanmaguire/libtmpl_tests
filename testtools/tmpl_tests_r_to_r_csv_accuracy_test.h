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
#ifndef TMPL_TESTS_R_TO_R_CSV_ACCURACY_TEST_H
#define TMPL_TESTS_R_TO_R_CSV_ACCURACY_TEST_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/helper/tmpl_abs.h>
#include <stddef.h>
#include <stdio.h>

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_R_TO_R_CSV_ACCURACY_TEST                                         *
 *  Purpose:                                                                  *
 *      Test functions of the form f: R -> R against a CSV.                   *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The data type (float, double, int, etc.).                         *
 *      csv:                                                                  *
 *          The path to the CSV file.                                         *
 *      f:                                                                    *
 *          The libtmpl function being tested.                                *
 ******************************************************************************/
#define TMPL_R_TO_R_CSV_ACCURACY_TEST(type, csv, f)                            \
int main(void)                                                                 \
{                                                                              \
    char buffer[1024];                                                         \
    char *line, *start, *end;                                                  \
    FILE *fp;                                                                  \
    const type real_zero = TMPL_CAST(0, type);                                 \
    long double max_abs_err = 0.0L;                                            \
    long double rms_abs_err = 0.0L;                                            \
    long double max_rel_err = 0.0L;                                            \
    long double rms_rel_err = 0.0L;                                            \
    long double count = 0.0L;                                                  \
    TMPL_OPEN_FILE(fp, csv);                                                   \
    line = fgets(buffer, sizeof(buffer), fp);                                  \
    while (line)                                                               \
    {                                                                          \
        const type x = TMPL_STRING_TO_REAL(x, line, &start);                   \
        const long double z = TMPL_STRING_TO_REAL(z, start + 1, &end);         \
        const type y_type = f(x);                                              \
        const long double y = TMPL_CAST(y_type, long double);                  \
        const long double abs_err = TMPL_ABS(y - z);                           \
        const long double rel_err = TMPL_ABS((y - z) / z);                     \
        if (abs_err > max_abs_err)                                             \
            max_abs_err = abs_err;                                             \
        if (rel_err > max_rel_err)                                             \
            max_rel_err = rel_err;                                             \
        if (z != real_zero)                                                    \
            rms_rel_err += rel_err * rel_err;                                  \
        rms_abs_err += abs_err * abs_err;                                      \
        line = fgets(buffer, sizeof(buffer), fp);                              \
        count += 1.0L;                                                         \
    }                                                                          \
    rms_abs_err = sqrtl(rms_abs_err / count);                                  \
    rms_rel_err = sqrtl(rms_rel_err / count);                                  \
    fclose(fp);                                                                \
    printf("\n");                                                              \
    printf("    max relative error: %.16LE\n", max_rel_err);                   \
    printf("    rms relative error: %.16LE\n", rms_rel_err);                   \
    printf("    max absolute error: %.16LE\n", max_abs_err);                   \
    printf("    rms absolute error: %.16LE\n", rms_abs_err);                   \
    return 0;                                                                  \
}

#endif
