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
#define indata {    \
    {0, 1},         \
    {1, 2},         \
    {2, 3},         \
    {3, 4},         \
    {4, 5},         \
    {5, 6},         \
    {6, 7}          \
}
#define outdata {1, 1, 1, 1, 1, 1, 1}
TMPL_R2_TO_R_ARRAY_EXACT_UNIT_TEST(
    unsigned long long int, tmpl_ULLong_GCD_Euclidean, indata, outdata
)
