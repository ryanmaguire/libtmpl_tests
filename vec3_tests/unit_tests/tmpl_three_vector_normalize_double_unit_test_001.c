/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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

#include <libtmpl/include/tmpl_vec3.h>
#include <math.h>
#include <float.h>
#include <stdio.h>

int main(void)
{
    const double val = DBL_MAX / 3.0;
    tmpl_ThreeVectorDouble P = tmpl_3DDouble_Rect(val, val, val);
    tmpl_ThreeVectorDouble u = tmpl_3DDouble_Normalize(&P);
    const double norm = tmpl_3DDouble_L2_Norm(&u);

    if (fabs(norm - 1.0) > 10.0*DBL_EPSILON)
        puts("FAIL");
    else
        puts("PASS");

    return 0;
}
