#include "../../../libtmpl_tests.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const size_t number_of_elements = TMPL_CAST(1E5, size_t);
    const size_t max_degree = 256;
    double *x = malloc(sizeof(*x) * number_of_elements);
    double *legendre = malloc(sizeof(*legendre) * (max_degree + 2));
    double *chebyshev = malloc(sizeof(*chebyshev) * (max_degree + 2));
    double *fresnel = malloc(sizeof(*fresnel) * max_degree);
    const double dx = 2.0 / TMPL_CAST(number_of_elements, double);
    size_t n, m;
    double rms_err = 0.0;
    double max_err = 0.0;
    double val, index, tmp;
    const double beta = 0.5;

    x[0] = -1.0;

    for (n = 1;  n < number_of_elements; ++n)
        x[n] = x[n - 1] + dx;

    for (n = 0; n < number_of_elements; ++n)
    {
        tmpl_Double_Legendre_P(legendre, x[n], max_degree + 2);
        tmpl_Double_Chebyshev_U(chebyshev, x[n], max_degree + 2);
	    tmpl_Double_Fresnel_Legendre_L(fresnel, x[n], beta, max_degree);

        for (m = 0; m < max_degree; ++m)
        {
            index = TMPL_CAST(m, double);
            val = (legendre[m] - x[n]*legendre[m+1]) / (index + 2.0) - beta*(chebyshev[m + 2] - 2.0*legendre[m + 2]);
            tmp = tmpl_Double_Abs(val - fresnel[m]);
            rms_err += tmp*tmp;

            if (tmp > max_err)
                max_err = tmp;
        }
    }

    rms_err = tmpl_Double_Sqrt(rms_err / TMPL_CAST(number_of_elements * max_degree, double));
    printf("%E\n%E\n", rms_err, max_err);
    free(x);
    free(legendre);
    free(fresnel);
    free(chebyshev);
    return 0;
}
