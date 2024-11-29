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
#ifndef TMPL_NSAMPS
#define TMPL_NSAMPS (1E7)
#endif
#include "../../tmpl_doubledouble_tests.h"

static inline __float128 add128(__float128 x, __float128 y)
{
    return x + y;
}

static inline tmpl_LongDoubleDouble
addLDD(tmpl_LongDoubleDouble x, tmpl_LongDoubleDouble y)
{
    return tmpl_LDoubleDouble_Quick_Add(&x, &y);
}

TMPL_TEST_MIXED_FUNC2_UNIT_TEST(
    tmpl_LongDoubleDouble,
    __float128,
    generate_pos_flt128l,
    compare_flt128l,
    fail_flt128l,
    addLDD,
    add128
)
