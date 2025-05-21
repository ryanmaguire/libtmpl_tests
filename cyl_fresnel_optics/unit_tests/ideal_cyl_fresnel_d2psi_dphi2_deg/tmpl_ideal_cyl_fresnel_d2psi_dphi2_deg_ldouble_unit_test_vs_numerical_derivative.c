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

/*  Geometric values for Saturn, Rev007.                                      */
static const long double k = 1.7453292519943294E+05L;
static const long double r = 8.76E+04L;
static const long double r0 = 8.75E+04L;
static const long double phi0 = 1.5E+02L;
static const long double B = 3.5E+01L;
static const long double D = 2.0E+05L;
static const long double eps = 1.0E-04L;
static const long double scale = 3.282806350011743794781694607995175500501E+03L;

/*  psi as a function of phi alone. Used for numerical differentiation.       */
static long double func(long double phi)
{
    return tmpl_LDouble_Ideal_Cyl_Fresnel_Psi_Deg(k, r, r0, phi, phi0, B, D);
}

int main(void)
{
    /*  There is a root for the second derivative near 13.75 degrees. The     *
     *  numerical second derivative will have poor relative error here, start *
     *  away from this value.                                                 */
    const long double start = 1.6E+01L;
    const long double end = 1.8E+02L;
    const long double dphi = 1.0E-03L;
    const long double h = 1.0E-02L;
    long double phi = start;

    while (phi < end)
    {
        const long double d2psi_approx =
            scale * tmpl_LDouble_Five_Point_Second_Derivative(func, phi, h);

        const long double d2psi =
            tmpl_LDouble_Ideal_Cyl_Fresnel_d2Psi_dPhi2_Deg(k, r, r0, phi, phi0, B, D);

        const long double err =
            tmpl_LDouble_Abs((d2psi - d2psi_approx) / d2psi);

        if (err > eps)
        {
            puts("FAIL");
            printf("phi       = %+.16LE\n", phi);
            printf("Exact     = %+.16LE\n", d2psi);
            printf("Numerical = %+.16LE\n", d2psi_approx);
            printf("Error     = %+.16LE\n", err);
            return -1;
        }

        phi += dphi;
    }

    puts("PASS");
    return 0;
}
