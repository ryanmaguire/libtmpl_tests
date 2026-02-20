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
#ifndef TMPL_TESTS_DIFF_PLOT_H
#define TMPL_TESTS_DIFF_PLOT_H
#include <libtmpl/include/compat/tmpl_cast.h>
#include <stdio.h>
#include <stdlib.h>

/*  Macro for plotting libtmpl functions using GNU Plot Utils.                */
#define TMPL_DIFF_PLOT(f0, f1, type, begin, finish, samples, filename)         \
int main(void)                                                                 \
{                                                                              \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const size_t number_of_samples = TMPL_CAST(samples, size_t);               \
    const type dx = (end - start) / TMPL_CAST(number_of_samples, type);        \
    type x = start;                                                            \
    FILE *fp = fopen("data.txt", "w");                                         \
    if (!fp)                                                                   \
    {                                                                          \
        puts("fopen failed and returned NULL.");                               \
        return -1;                                                             \
    }                                                                          \
    while (x <= end)                                                           \
    {                                                                          \
        const type y0 = f0(x);                                                 \
        const type y1 = f1(x);                                                 \
        const type err = (y1 - y0) / y1;                                       \
        const long double xl = TMPL_CAST(x, long double);                      \
        const long double errl = TMPL_CAST(err, long double);                  \
        fprintf(fp, "%.40LE %.40LE\n", xl, errl);                              \
        x += dx;                                                               \
    }                                                                          \
    fclose(fp);                                                                \
    system("graph -T ps data.txt > " filename);                                \
    system("rm -f data.txt");                                                  \
    return 0;                                                                  \
}
/*  End of TMPL_DIFF_PLOT macro.                                              */

#endif
