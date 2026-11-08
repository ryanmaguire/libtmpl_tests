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
#ifndef TMPL_NSAMPS
#define TMPL_NSAMPS (1E6)
#endif
#include "../../../libtmpl_tests.h"
#include <mpfr.h>
#undef TMPL_DEFAULT_TOLERANCE
#define TMPL_DEFAULT_TOLERANCE (1)

static long double
asin_precise(const long double x)
{
    mpfr_t mx, result;
    long double y;
    mpfr_init2(mx, 128);
    mpfr_init2(result, 128);
    mpfr_set_ld(mx, x, MPFR_RNDN);
    mpfr_asin(result, mx, MPFR_RNDN);
    y = mpfr_get_ld(result, MPFR_RNDN);
    mpfr_clear(mx);
    mpfr_clear(result);
    return y;
}

TMPL_R_TO_R_VS_INTERVAL_UNIT_TEST(
    long double,
    -1.0E0L,
    +1.0E0L,
    tmpl_LDouble_Arcsin,
    asin_precise
)
