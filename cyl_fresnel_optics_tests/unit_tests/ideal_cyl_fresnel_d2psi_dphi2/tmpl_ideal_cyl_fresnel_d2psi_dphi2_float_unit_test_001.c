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
static const float k = 175000.0F;
static const float r = 8.76E+04F;
static const float r0 = 8.75E+04F;
static const float phi = 2.75F;
static const float phi0 = 2.5F;
static const float B = 5.0E-01F;
static const float D = 2.0E+05F;
static const float answer = 5.66151172390706394942820442124343701920318279E+09F;
#define ARG k COMMA r COMMA r0 COMMA phi COMMA phi0 COMMA B COMMA D

TMPL_RN_TO_R_SINGLE_UNIT_TEST(
    float, tmpl_Float_Ideal_Cyl_Fresnel_d2Psi_dPhi2, ARG, answer
)
