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
#include "../../../libtmpl_tests.h"
#include <Vector3D.h>
void component(struct v3D64_t * const p, const struct v3D64_t * const q)
{
    double factor;
    struct v3D64_t qn = *q;
    Vector3D_Normalize_flt64(&qn);
    factor = Vector3D_ScalarProduct_flt64(p, &qn);
    Vector3D_Mul_flt64(&qn, factor);
    *p = qn;
}

TMPL_THREEVEC2_VS_XYZ_TIME_TESTS(
    double,
    tmpl_ThreeVectorDouble,
    struct v3D64_t,
    tmpl_3DDouble_Component,
    component
)
