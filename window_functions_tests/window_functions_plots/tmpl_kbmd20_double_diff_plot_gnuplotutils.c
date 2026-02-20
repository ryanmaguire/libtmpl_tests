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
#include "../../libtmpl_tests.h"
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_window_functions.h>
#include <libtmpl/include/constants/tmpl_math_constants.h>
#include <gsl/gsl_specfunc.h>

static double func(const double x, const double width)
{
    const double c = 2.0 * x / width;
    const double arg = 1.0 - c * c;
    const double alpha = 2.0 * tmpl_double_pi;
    double numer, denom;

    if (arg < 0.0)
        return 0.0;

    numer = gsl_sf_bessel_I0(alpha * tmpl_Double_Sqrt(arg)) - 1.0;
    denom = gsl_sf_bessel_I0(alpha) - 1.0;
    return numer / denom;
}

static inline double f0(const double x)
{
    return tmpl_Double_KBMD20(x, 1.0);
}

static inline double f1(const double x)
{
    return func(x, 1.0);
}

TMPL_DIFF_PLOT(f0, f1, double, 0.0, 0.49, 1E4, "tmpl_kb2_diff_plot.ps")
