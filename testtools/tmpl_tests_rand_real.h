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
 *  1.) tmpl_cast.h:                                                          *
 *          Header file with the TMPL_CAST macro for C vs. C++ compatibility. *
 *  2.) stdlib.h:                                                             *
 *          rand and RAND_MAX provided here.                                  *
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
#ifndef TMPL_TESTS_RAND_REAL_H
#define TMPL_TESTS_RAND_REAL_H

/*  TMPL_CAST, providing C vs. C++ compatibility, found here.                 */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  rand function found here, as is the RAND_MAX macro.                       */
#include <stdlib.h>

/*  Given a type (double, float, or long double), compute a pseudo-random     *
 *  real number between 0 and 1 and store the result in val.                  */
#define TMPL_RAND_REAL(type, val)                                              \
do {                                                                           \
    const int my_temp_variable = rand();                                       \
    val = TMPL_CAST(my_temp_variable, type) / TMPL_CAST(RAND_MAX, type);       \
} while(0);

#endif
/*  End of include guard.                                                     */
