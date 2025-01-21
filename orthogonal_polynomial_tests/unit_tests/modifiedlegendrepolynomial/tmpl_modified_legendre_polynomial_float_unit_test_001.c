#include "../../../libtmpl_tests.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const size_t number_of_elements = TMPL_CAST(1E5, size_t);
    const size_t max_degree = 128;
    float *x = malloc(sizeof(*x) * number_of_elements);
    float *legendre = malloc(sizeof(*legendre) * (max_degree + 1));
    float *modified = malloc(sizeof(*modified) * max_degree);
    float *precompute = malloc(sizeof(*precompute) * max_degree);
    const float dx = 2.0F / TMPL_CAST(number_of_elements, float);
    size_t n, m;
    float rms_err = 0.0F;
    float max_err = 0.0F;

    x[0] = -1.0F;

    for (n = 1;  n < number_of_elements; ++n)
        x[n] = x[n - 1] + dx;

    for (n = 0; n < number_of_elements; ++n)
    {
        tmpl_Float_Legendre_P(legendre, x[n], max_degree + 1);
        tmpl_Float_Modified_Legendre_P(modified, x[n], max_degree);
        tmpl_Float_Modified_Legendre_P_Precompute(precompute, legendre, max_degree);

        for (m = 0; m < max_degree; ++m)
        {
            const float tmp = tmpl_Float_Abs(modified[m] - precompute[m]);
            rms_err += tmp*tmp;

            if (tmp > max_err)
                max_err = tmp;
        }
    }

    rms_err = tmpl_Float_Sqrt(rms_err / TMPL_CAST(number_of_elements * max_degree, float));
    printf("%E\n%E\n", TMPL_CAST(rms_err, double), TMPL_CAST(max_err, double));
    free(x);
    free(legendre);
    free(modified);
    free(precompute);
    return 0;
}
