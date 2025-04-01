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

#define indata {                          \
    {+1.0E8L, +1.0L}, /* Mostly North. */ \
    {-1.0E8L, +1.0L}, /* Mostly South. */ \
    {+1.0E8L, -1.0L}, /* Mostly North. */ \
    {-1.0E8L, -1.0L}  /* Mostly South. */ \
}

#define outdata {                                 \
    +1.5707963167948966192313220249730847754319L, \
    -1.5707963167948966192313220249730847754319L, \
    +1.5707963367948966192313213583064181087653L, \
    -1.5707963367948966192313213583064181087653L  \
}

TMPL_R2_TO_R_ARRAY_UNIT_TEST(
    long double, tmpl_LDouble_Arctan2, indata, outdata
)
