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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 5, 2022                                             *
 ******************************************************************************/
#include "../../../libtmpl_tests.h"
#define indata {DNUML, -DNUML}
#define outdata {DNUML, DNUML}
TMPL_REAL_FUNC_ARRAY_VS_ANSWER_EXACT(
    long double, tmpl_LDouble_Abs, indata, outdata
)
