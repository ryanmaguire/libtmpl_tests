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
static const float k = 1.7453292519943294E+05F;
static const float r = 8.76E+04F;
static const float r0 = 8.75E+04F;
static const float phi0 = 2.62F;
static const float B = 6.1E-01F;
static const float D = 2.0E+05F;
static const float eps = 1.0E-04F;

int main(void)
{
    /*  There is a root for the second derivative near 0.24 radians. The      *
     *  relative error will likely be poorer here. Start after this point.    */
    const float start = 3.0E-01F;
    const float end = tmpl_Float_Pi;
    const float dphi = 1.0E-05F;
    float phi = start;

    while (phi < end)
    {
        const double d2psi_double = tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2(
            TMPL_CAST(k, double),
            TMPL_CAST(r, double),
            TMPL_CAST(r0, double),
            TMPL_CAST(phi, double),
            TMPL_CAST(phi0, double),
            TMPL_CAST(B, double),
            TMPL_CAST(D, double)
        );

        const float d2psi = TMPL_CAST(d2psi_double, float);
        const float d2psi_approx = tmpl_Float_Cyl_Fresnel_d2Psi_dPhi2(
            k, r, r0, phi, phi0, B, D
        );

        const float err = tmpl_Float_Abs((d2psi - d2psi_approx) / d2psi);

        if (err > eps)
        {
            puts("FAIL");
            printf("phi       = %+.16E\n", TMPL_CAST(phi, double));
            printf("Exact     = %+.16E\n", TMPL_CAST(d2psi, double));
            printf("Numerical = %+.16E\n", TMPL_CAST(d2psi_approx, double));
            printf("Error     = %+.16E\n", TMPL_CAST(err, double));
            return -1;
        }

        phi += dphi;
    }

    puts("PASS");
    return 0;
}
