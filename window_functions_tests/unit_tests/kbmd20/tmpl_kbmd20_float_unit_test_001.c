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
static float kbmd20f(const float x)
{
    const double x_double = TMPL_CAST(x, double);
    const double kbmd20_x = tmpl_Double_KBMD20(x_double, 1.0);
    return TMPL_CAST(kbmd20_x, float);
}
static double kbmd20(const double x)
{
    return tmpl_Double_KBMD20(x, 1.0);
}
TMPL_R_TO_R_VS_FROM_INTERVAL_UNIT_TEST(
    float, -0.5F, 0.5F, kbmd20, kbmd20f
)
