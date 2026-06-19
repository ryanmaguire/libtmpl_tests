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
float Vector3D_Angle_flt32(const struct v3D32_t * p, const struct v3D32_t * q)
{
    struct v3D32_t cross = *p;
    const float dot_product = Vector3D_ScalarProduct_flt32(p, q);
    float cross_norm;
    Vector3D_VectorProduct_flt32(&cross, q);
    cross_norm = Vector3D_Abs_flt32(&cross);
    return atan2(cross_norm, dot_product);
}
TMPL_THREEVEC2_TO_R_VS_XYZ_TIME_TESTS(
    float,
    tmpl_ThreeVectorFloat,
    struct v3D32_t,
    tmpl_3DFloat_Angle,
    Vector3D_Angle_flt32
)
