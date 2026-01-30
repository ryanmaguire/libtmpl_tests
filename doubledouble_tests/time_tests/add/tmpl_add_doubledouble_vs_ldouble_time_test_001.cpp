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
#include "../../tmpl_doubledouble_tests.hpp"

static inline long double addld(long double x, long double y)
{
    return x + y;
}

static inline tmpl_DoubleDouble addDD(tmpl_DoubleDouble x, tmpl_DoubleDouble y)
{
    return tmpl_DoubleDouble_Add(&x, &y);
}

TMPL_TEST_MIXED_FUNC2_TIME_TEST(
    tmpl_DoubleDouble,
    long double,
    generate_ld,
    get_ld_error,
    addDD,
    addld
)
