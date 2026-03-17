#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/types/tmpl_cubic_double.h>
#include <libtmpl/include/tmpl_interpolate.h>
#include <libtmpl/include/tmpl_math.h>
#include <stdio.h>

#define LEN 100
#define NEW_LEN 1000
#define END 10.0

int main(void)
{
    double x[LEN];
    double y[LEN];
    double x_new[NEW_LEN];
    double y_new[NEW_LEN];
    double dx;
    size_t n, m;
    tmpl_CubicDouble p[LEN - 1];

    for (n = 0; n < LEN; ++n)
    {
        x[n] = (double)n * END / LEN + 0.5 * tmpl_Double_Sin((double)n * END / LEN);
        y[n] = (double)n * END / LEN + 0.5 * tmpl_Double_Cos((double)n * END / LEN);

        fprintf(stderr, "%E, %E\n", x[n], y[n]);
    }

    dx = (2.0 + END) / NEW_LEN;

    for (n = 0; n < NEW_LEN; ++n)
        x_new[n] = dx * (double)n - 1.0;

    tmpl_Double_Natural_Cubic_Spline(x, y, p, LEN);
    tmpl_Double_Sorted_Cubic_Interp1d(x, y, p, LEN, x_new, y_new, NEW_LEN);

    for (n = 0; n < NEW_LEN; ++n)
        printf("%E, %E\n", x_new[n], y_new[n]);

    return 0;
}
