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
#include "../../../libtmpl_tests.h"
#include <cerf.h>
static float im_w_of_xf(float x)
{
    double x_double = TMPL_CAST(x, double);
    double im_w_of_x_double = im_w_of_x(x_double);
    return TMPL_CAST(im_w_of_x_double, float);
}
TMPL_TEST_REAL_FUNC_VS_REAL_FUNC_UNIT_TEST(
    float, -1.0E0F, 1.0E0F, tmpl_Float_Faddeeva_Im, im_w_of_xf
)
