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
#include "../../../libtmpl_tests.h"
#define indata {        \
    {1.0L, 1.0L, 1.0L}, \
    {2.0L, 1.0L, 1.0L}, \
    {3.0L, 2.0L, 1.0L}, \
    {0.5F, 2.0L, 1.0L}  \
}

#define outdata {       \
    {{+0.00L, +1.00L}}, \
    {{+1.00L, +1.00L}}, \
    {{+1.00L, +1.00L}}, \
    {{-0.25L, +1.00L}}  \
}

TMPL_R3_TO_TWOVEC_ARRAY_UNIT_TEST(
    long double,
    tmpl_AffineLongDouble,
    tmpl_AffLDouble_Point_Intercept,
    indata,
    outdata
)
