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
#include "../tmpl_polynomial_integer_unit_tests.h"
#define func tmpl_IntPolynomial_Add_Same_Degree
#define pdat {1, 2, 3, 4}
#define qdat {5, 6, 7, 8}
#define rdat {6, 8, 10, 12}
#define type int
#define ptype tmpl_IntPolynomial
#define pcreate tmpl_IntPolynomial_Create_From_Data
#define destroy tmpl_IntPolynomial_Destroy
TEST1(func, pdat, qdat, rdat, type, ptype, pcreate, destroy)
