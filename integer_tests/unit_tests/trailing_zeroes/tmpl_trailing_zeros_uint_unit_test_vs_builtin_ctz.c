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
#define TMPL_NSAMPS (65535)
#endif
#include "../../../libtmpl_tests.h"
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
static int trailing_zeros(unsigned int n)
{
    unsigned long index;
    if (n == 0)
        return 0;
    _BitScanForward(&index, n);
    return (int)index;
}
#else
static int trailing_zeros(unsigned int n)
{
    return (n == 0 ? 0 : __builtin_ctz(n));
}
#endif
TMPL_R_TO_R_VS_FROM_INTERVAL_EXACT_UNIT_TEST(
    unsigned int, 0, 65535, tmpl_UInt_Trailing_Zeros, trailing_zeros
)
