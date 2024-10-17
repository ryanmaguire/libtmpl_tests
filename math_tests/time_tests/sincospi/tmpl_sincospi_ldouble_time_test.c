/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************/
#include "tmpl_math_time_tests.h"
#define ONE_PI (3.14159265358979323846264338327950288419716939937510582097494L)
static void func(long double t, long double *s, long double *c)
{
    const long double arg = ONE_PI*fmodl(t, 2.0L);
    *s = sinl(arg);
    *c = cosl(arg);
}
TEST4(long double, -2.0L, 2.0L, tmpl_LDouble_SinCosPi, func)
