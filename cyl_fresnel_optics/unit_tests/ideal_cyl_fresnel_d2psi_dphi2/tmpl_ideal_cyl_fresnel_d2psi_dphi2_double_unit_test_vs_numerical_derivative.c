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
static const double k = 1.7453292519943294E+05;
static const double r = 8.76E+04;
static const double r0 = 8.75E+04;
static const double phi0 = 2.62;
static const double B = 6.1E-01;
static const double D = 2.0E+05;
static const double eps = 1.0E-04;

/*  psi as a function of phi alone. Used for numerical differentiation.       */
static double func(double phi)
{
    return tmpl_Double_Ideal_Cyl_Fresnel_Psi(k, r, r0, phi, phi0, B, D);
}

int main(void)
{
    /*  There is a root for the second derivative near 0.24 radians. The      *
     *  numerical second derivative will have poor relative error here, start *
     *  away from this value.                                                 */
    const double start = 3.0E-01;
    const double end = tmpl_Double_Pi;
    const double dphi = 1.0E-05;
    const double h = 1.0E-02;
    double phi = start;

    while (phi < end)
    {
        const double d2psi_approx = tmpl_Double_Five_Point_Second_Derivative(
            func, phi, h
        );

        const double d2psi = tmpl_Double_Ideal_Cyl_Fresnel_d2Psi_dPhi2(
            k, r, r0, phi, phi0, B, D
        );

        const double err = tmpl_Double_Abs((d2psi - d2psi_approx) / d2psi);

        if (err > eps)
        {
            puts("FAIL");
            printf("phi       = %+.16E\n", phi);
            printf("Exact     = %+.16E\n", d2psi);
            printf("Numerical = %+.16E\n", d2psi_approx);
            printf("Error     = %+.16E\n", err);
            return -1;
        }

        phi += dphi;
    }

    puts("PASS");
    return 0;
}
