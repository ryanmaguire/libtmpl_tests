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
 *  Purpose:                                                                  *
 *      Provides the TMPL_RAND_REAL macro. Used for creating pseudo-random    *
 *      real numbers between 0 and 1 of a given type.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Provides string-to-float functions.                               *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   July 19, 2024                                                     *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/01: Ryan Maguire                                                  *
 *      Moved macro out of libtmpl_tests.h to this file.                      *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef LIBTMPL_TESTS_STRING_TO_REAL_H
#define LIBTMPL_TESTS_STRING_TO_REAL_H

/*  strtold, strtod, and strtof all found here.                               */
#include <stdlib.h>

/*  Converts a string to a real of the appropriate type.                      */
#define TMPL_STRING_TO_REAL(x, start, end) _Generic((x),                       \
    long double: strtold,                                                      \
    default:     strtod,                                                       \
    float:       strtof                                                        \
)(start, end)

#endif
/*  End of include guard.                                                     */
