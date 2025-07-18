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
#define IN_VAL tmpl_Double_Sqrt(DNUM)
#define OUT_VAL 2.0 * DNUM
#define inarr {             \
    {{+IN_VAL, +IN_VAL}},   \
    {{+IN_VAL, -IN_VAL}},   \
    {{-IN_VAL, +IN_VAL}},   \
    {{-IN_VAL, -IN_VAL}}    \
}
#define outarr {OUT_VAL, OUT_VAL, OUT_VAL, OUT_VAL}
TMPL_C_TO_R_ARRAY_UNIT_TEST(
    tmpl_ComplexDouble, double, tmpl_CDouble_Abs_Squared, inarr, outarr
)
