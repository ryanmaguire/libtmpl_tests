/******************************************************************************
 *                                  LICENSE                                   *
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
#include <libtmpl/include/tmpl.h>
#include "tmpl_vec3_time_tests.h"
double
tmpl_3DDouble_Quick_Large_Angle(const tmpl_ThreeVectorDouble * const P,
                                const tmpl_ThreeVectorDouble * const Q)
{
    double norm_p, norm_q, dot_prod;
    norm_p = tmpl_3DDouble_L2_Norm(P);

    if (norm_p == 0.0)
        return 0.0;

    norm_q = tmpl_3DDouble_L2_Norm(Q);

    if (norm_q == 0.0)
        return 0.0;

    dot_prod = tmpl_3DDouble_Dot_Product(P, Q);

    return tmpl_Double_Arccos(dot_prod / (norm_p * norm_q));
}

TEST9(double, tmpl_ThreeVectorDouble, tmpl_ThreeVectorDouble,
      tmpl_3DDouble_Angle, tmpl_3DDouble_Quick_Large_Angle)
