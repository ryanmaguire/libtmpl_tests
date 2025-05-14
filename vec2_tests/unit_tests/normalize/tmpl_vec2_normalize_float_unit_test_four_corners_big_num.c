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
#define VAL 7.071067811865475244008443621048490392848359376884740365883399E-01F
#define inarr {           \
    {{+BNUMF, +BNUMF}},   \
    {{+BNUMF, -BNUMF}},   \
    {{-BNUMF, +BNUMF}},   \
    {{-BNUMF, -BNUMF}}    \
}

#define outarr {    \
    {{+VAL, +VAL}}, \
    {{+VAL, -VAL}}, \
    {{-VAL, +VAL}}, \
    {{-VAL, -VAL}}  \
}

TMPL_TWOVEC_TO_TWOVEC_ARRAY_UNIT_TEST(
    tmpl_TwoVectorFloat, float, tmpl_2DFloat_Normalize, inarr, outarr
)
