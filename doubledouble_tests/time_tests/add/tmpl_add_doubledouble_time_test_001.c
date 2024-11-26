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
#include "../../tmpl_doubledouble_tests.h"

static inline __float128 add128(__float128 x, __float128 y)
{
    return x + y;
}

static inline tmpl_DoubleDouble addDD(tmpl_DoubleDouble x, tmpl_DoubleDouble y)
{
    return tmpl_DoubleDouble_Add(&x, &y);
}

TMPL_TEST_MIXED_FUNC2_TIME_TEST(
    tmpl_DoubleDouble,
    __float128,
    generate_flt128,
    get_flt128_error,
    addDD,
    add128
)
