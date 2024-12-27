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
#define TMPL_NSAMPS (3E8)
#endif
#include "../../../libtmpl_tests.h"
static double sincpi(double x)
{
    if (x == 0.0)
        return 1.0;

    return tmpl_Double_SinPi(x) / (tmpl_Double_Pi * x);
}
TMPL_TEST_REAL_FUNC_VS_REAL_FUNC_TIME_TEST(
    double, -5.0E-01, 5.0E-01, tmpl_Double_SincPi, sincpi
)