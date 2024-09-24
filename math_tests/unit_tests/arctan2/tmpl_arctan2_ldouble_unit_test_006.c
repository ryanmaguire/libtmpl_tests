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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 5, 2022                                              *
 ******************************************************************************/
#include "../../../libtmpl_tests.h"
#define indata {{0.0L, 1.0L}, {-0.0L, 1.0L}, {-0.0L, -1.0L}, {0.0L, -1.0L}}
TMPL_REAL2_FUNC_VS_REAL2_FUNC_FROM_ARRAY(
    long double, tmpl_LDouble_Arctan2, atan2l, indata
)