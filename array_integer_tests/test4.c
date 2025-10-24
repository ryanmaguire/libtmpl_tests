#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <libtmpl/include/tmpl.h>

static double
naive_sum(const signed long long *arr, size_t len)
{
    double sum = 0.0;
    size_t i;
    for (i = 0; i < len; ++i)
        sum += (double)arr[i];
    return sum;
}

static signed long long
llong_sum(const signed long long *arr, size_t len)
{
    signed long long sum = 0;
    size_t i;
    for (i = 0; i < len; ++i)
        sum += arr[i];
    return sum;
}

static __int128
exact_sum(const signed long long *arr, size_t len)
{
    __int128 sum = 0;
    size_t i;
    for (i = 0; i < len; ++i)
        sum += arr[i];
    return sum;
}

static double
int128_to_double(__int128 x)
{
    if (x > 0)
        return (double)(unsigned __int128)x;
    else
        return -(double)(unsigned __int128)(-x);
}

static double
relative_error(double approx, __int128 exact)
{
    double exact_d = int128_to_double(exact);
    if (exact_d == 0.0)
        return fabs(approx);

    return fabs((approx - exact_d) / exact_d);
}

static double
llong_to_double(signed long long x)
{
    return (double)x;
}

static double
wall_time(void)
{
    return (double)clock() / (double)CLOCKS_PER_SEC;
}

int main(void)
{
    const size_t N = 100000000;
    signed long long *arr = malloc(N * sizeof(*arr));
    size_t i;

    if (!arr)
    {
        puts("malloc failed.");
        return -1;
    }

    srand(0xC0FFEE);

    for (i = 0; i < N; ++i)
    {
        signed long long hi = (rand() % 20000) - 10000;
        signed long long lo = rand() & 0xFFFF;
        arr[i] = (hi << 32) | lo;
    }

    double t1 = wall_time();
    double sum_comp = tmpl_LLong_Array_Double_Sum(arr, N);
    double t2 = wall_time();

    double t3 = wall_time();
    double sum_naive = naive_sum(arr, N);
    double t4 = wall_time();

    double t5 = wall_time();
    signed long long sum_ll = llong_sum(arr, N);
    double t6 = wall_time();

    double t7 = wall_time();
    __int128 exact = exact_sum(arr, N);
    double t8 = wall_time();

    double err_comp  = relative_error(sum_comp, exact);
    double err_naive = relative_error(sum_naive, exact);
    double err_ll    = relative_error(llong_to_double(sum_ll), exact);

    printf("------------------------------------------------------------\n");
    printf("  Exact (128-bit):  %.0Lf\n", (long double)exact);
    printf("  Compensated Sum:  %.17g\n", sum_comp);
    printf("  Naive Sum:        %.17g\n", sum_naive);
    printf("  Native long long: %lld\n", sum_ll);
    printf("------------------------------------------------------------\n");
    printf("  Compensated error: %.3e\n", err_comp);
    printf("  Naive error:       %.3e\n", err_naive);
    printf("  long long error:   %.3e\n", err_ll);
    printf("------------------------------------------------------------\n");
    printf("  Compensated time: %.3f sec  (%.3f ns/elem)\n",
           t2 - t1, 1e9 * (t2 - t1) / N);
    printf("  Naive time:       %.3f sec  (%.3f ns/elem)\n",
           t4 - t3, 1e9 * (t4 - t3) / N);
    printf("  long long time:   %.3f sec  (%.3f ns/elem)\n",
           t6 - t5, 1e9 * (t6 - t5) / N);
    printf("  __int128 time:    %.3f sec  (%.3f ns/elem)\n",
           t8 - t7, 1e9 * (t8 - t7) / N);
    printf("------------------------------------------------------------\n");

    free(arr);
    return 0;
}
