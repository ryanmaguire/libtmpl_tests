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
static const long double k = 175000.0L;
static const long double r = 8.76E+04L;
static const long double r0 = 8.75E+04L;
static const long double phi = 1.5E+02L;
static const long double phi0 = 1.75E+02L;
static const long double B = 3.0E+01L;
static const long double D = 2.0E+05L;
static const long double answer = 5.44732137271094924474214127762279103942E+09L;
#define ARG k COMMA r COMMA r0 COMMA phi COMMA phi0 COMMA B COMMA D

TMPL_RN_TO_R_SINGLE_UNIT_TEST(
    long double, tmpl_LDouble_Ideal_Cyl_Fresnel_d2Psi_dPhi2_Deg, ARG, answer
)
